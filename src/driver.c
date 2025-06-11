#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"

int search_depth = 6;
int bestMove = 0; //ERROR IS HERE?
void recalibrate(){
    int bits = count_1s(occupancies[both]);
    if(bits < 25){
        search_depth = 7;
    }
    else if(bits < 20){
        search_depth = 8;
    }
    else if(bits < 12){
        search_depth = 9;
    }
    else if(bits < 8){
        search_depth = 10;
    }
    else if(bits < 5){
        search_depth = 12;
    }
}

int playBestMove() {
    recalibrate();
    int bestMove = getBestMove(search_depth);
    if(bestMove == 1) {
        // printf("Best move: ");
        // PRINT_MOVE(bestMove);
        makeMove(bestMove, all);
        // printBoard();
    } else {
        if(bestMove < 0) printf("Checkmate\n");
        else if(bestMove == 0) printf("Draw\n");
    }
    return bestMove;
}

int playBestFromFen(char* fen) {
    parseFen(fen);
    return playBestMove();
}

void oneVsOne(){ 
    // parseFen(start_position);
    // char player = 'W';
    // char *move = (char *)malloc(10 * sizeof(char));

    // while(1) {
    //     printf("Player %c's turn. Enter your move: ", player);
    //     fgets(move, 10, stdin);
    //     move[strcspn(move, "\n")] = 0;  // Remove newline character

    //     if(strcmp(move, "exit") == 0) {
    //         printf("Exiting game.\n");
    //         free(move);
    //         return;
    //     }

    //     int promotionFlag = 0;

    //     if((move[0] == 'P'|| move[0] == 'p') && (squareToPos(move + 3) < h8 || squareToPos(move + 3) > a1)) {
    //         promotionFlag = 1;
    //     }

    //     if(!makePlayerMove(move, promotionFlag)) {
    //         printf("Invalid move. Try again.\n");
    //     }

    //     player = (player == 'W') ? 'B' : 'W'; // Switch player
    //     printBoard();
    // }
}

void init() {
    nodes = 0;
    bestMove = 0;
    initAttackTables();
    initRandomizingRoutines();
}

void cleanup(){
    // for(int i = 0; i < 64; i++) {
    //     free(mBishopTable[i]);
    //     free(mRookTable[i]);
    // }
    // printf("Cleanup done.\n");
}

uint64 unix_time_ms() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64 t = ((uint64)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    // FILETIME is in 100-nanosecond intervals since Jan 1, 1601
    // Convert to milliseconds since Unix epoch (Jan 1, 1970)
    return (t - 116444736000000000ULL) / 10000ULL;
}
