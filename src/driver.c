#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"

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
