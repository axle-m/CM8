#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"
#include "boardState.h"

static inline void runTests() {
    double averages[7];
    for(int i = 1; i < 8; i++) {
        int temp_depth = i;
        uint64 total = 0;
        printf("running test at depth %d\n", temp_depth);

        parseFen(start_position);
        printf("Testing position: %s\n", start_position);
        printBoard();
        uint64 start_time = unix_time_ms();
        int move = getBestMove(temp_depth);
        uint64 end_time = unix_time_ms();
        uint64 elapsed_time = end_time - start_time;
        total += elapsed_time;
        printf("Elapsed time for depth %d: %llu ms\n", temp_depth, elapsed_time);
        printf("Best move: ");
        PRINT_MOVE(move);
        printf("\n");

        parseFen(tricky_position);
        printf("Testing position: %s\n", tricky_position);
        printBoard();
        start_time = unix_time_ms();
        move = getBestMove(temp_depth);
        end_time = unix_time_ms();
        elapsed_time = end_time - start_time;
        total += elapsed_time;
        printf("Elapsed time for depth %d: %llu ms\n", temp_depth, elapsed_time);
        printf("Best move: ");
        PRINT_MOVE(move);
        printf("\n");

        parseFen(killer_position);
        printf("Testing position: %s\n", killer_position);
        printBoard();
        start_time = unix_time_ms();
        move = getBestMove(temp_depth);
        end_time = unix_time_ms();
        elapsed_time = end_time - start_time;
        total += elapsed_time;
        printf("Elapsed time for depth %d: %llu ms\n", temp_depth, elapsed_time);
        printf("Best move: ");
        PRINT_MOVE(move);
        printf("\n");

        // parseFen(cmk_position);
        // printf("Testing position: %s\n", cmk_position);
        // printBoard();
        // start_time = unix_time_ms();
        // move = getBestMove(temp_depth);
        // end_time = unix_time_ms();
        // elapsed_time = end_time - start_time;
        // total += elapsed_time;
        // printf("Elapsed time for depth %d: %llu ms\n", temp_depth, elapsed_time);
        // printf("Best move: ");
        // PRINT_MOVE(move);
        // printf("\n");

        averages[i - 1] = (double)(total) / 3.0;
        printf("Average time for depth %d: %.2f ms\n", temp_depth, averages[i - 1]);
    }

    for(int i = 0; i < 7; i++) {
        printf("Average time for depth %d: %.2f ms\n", i + 1, averages[i]);
    }
}

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    cleanup();
    return 0;
}