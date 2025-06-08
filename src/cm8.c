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

    parseFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq c6 0 1");
    printBoard();

    COPY_BOARD;

    parseFen(empty_board);
    printBoard();

    TAKE_BACK;

    printBoard();

    cleanup();
    return 0;
}