#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    SET_BIT(bitboards[P], e2);
    printBitboard(bitboards[P]);

    printf("piece on e2: %c\n", asciiPieces[P]);

    cleanup();
    return 0;
}