#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"

typedef struct boardState {
    uint64 bitboards[12];
    uint64 occupancies[3];
    int side;
    int enpassant;
    int castle;
} boardState;

static inline boardState *storeBoardState() {
    boardState *board = (boardState *)malloc(sizeof(boardState));
    memcpy(board->bitboards, bitboards, 96);
    memcpy(board->occupancies, occupancies, 24);
    board->side = side;
    board->enpassant = enpassant;
    board->castle = castle;
    return board;
}

static inline void getBoardState(boardState *board) {
    printf("Board state : 0x%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%llx%x%x%x\n", 
        board->bitboards[0], board->bitboards[1], board->bitboards[2], board->bitboards[3], 
        board->bitboards[4], board->bitboards[5], board->bitboards[6], board->bitboards[7], 
        board->bitboards[8], board->bitboards[9], board->bitboards[10], board->bitboards[11],
        board->occupancies[0], board->occupancies[1], board->occupancies[2],
        board->side, board->enpassant, board->castle);
}

static inline void restoreState(boardState *board) {
    memcpy(bitboards, board->bitboards, 96);
    memcpy(occupancies, board->occupancies, 24);
    side = board->side;
    enpassant = board->enpassant;
    castle = board->castle;
}

static inline void freeBoardState(boardState *board) {
    free(board);
}