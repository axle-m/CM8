#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"
#include "boardState.h"

int search_depth = 4;

static inline void recalibrate(){
    int bits = count_1s(occupancies[both]);
    if(bits < 25){
        search_depth = 5;
    }
    else if(bits < 20){
        search_depth = 6;
    }
    else if(bits < 12){
        search_depth = 8;
    }
    else if(bits < 8){
        search_depth = 10;
    }
    else if(bits < 5){
        search_depth = 12;
    }
}

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
        recalibrate();
        printf("Current depth: %d\n", search_depth);
        uint64 time = unix_time_ms();
        int START_TIME = time;
        int move = getBestMove(search_depth);
        uint64 taken = unix_time_ms() - time;
        makeMove(move, all);
        printBoard();
        printf("took %llu ms\n", taken);
        getchar();
    }

    cleanup();
    return 0;
}