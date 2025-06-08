#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"
#include "boardState.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    parseFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    printBoard();

    moveList list[1];
    initMoveList(list);
    generateMoves(list);

    for(int i = 0; i < list->count; i++) {
        int move = list->moves[i];
        PRINT_MOVE_COMPLETE(move);
        COPY_BOARD;
        makeMove(move, all);
        printBoard();
        getchar();
        TAKE_BACK;
        printBoard();
        getchar();

    }

    cleanup();
    return 0;
}