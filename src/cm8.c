#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    parseFen(start_position);
    printBoard();

    printAttackedSquares(white);
    printAttackedSquares(black);

    cleanup();
    return 0;
}