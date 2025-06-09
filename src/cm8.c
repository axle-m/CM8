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

    parseFen(start_position);
    makePlayerMove("Pe2e4", 0);
    makePlayerMove("pe7e5", 0);
    printBoard();
    printBitboard(bitboards[P]);

    cleanup();
    return 0;
}