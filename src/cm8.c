#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"
#include "boardState.h"

#define depth 4

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    parseFen(start_position);
    printf("Initial board:\n");
    printBoard();

    // uint64 time = unix_time_ms();
    // int bestMove = getBestMove(depth);
    // uint64 taken = unix_time_ms() - time;
    // PRINT_MOVE_COMPLETE(bestMove);
    // printf("Time taken: %llu ms\n", taken);

    while(1){
        int move = getBestMove(depth);
        makeMove(move, all);
        printBoard();
        getchar();
    }

    cleanup();
    return 0;
}