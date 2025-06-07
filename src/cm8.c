#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    printBitboard(occupancies[both]);
    printBitboard(occupancies[white]);
    printBitboard(occupancies[black]);

    printBoard();

    cleanup();
    return 0;
}