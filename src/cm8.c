#include <stdio.h>
#include <string.h>

#include "bit.h"
#include "attackTables.h"
#include "inputProcessor.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    U64 bitboard = 0ULL;
    U64 block = 0ULL;

    SET_BIT(block, d8);
    SET_BIT(block, c4);
    SET_BIT(block, g4);
    SET_BIT(block, d2);
    SET_BIT(block, d1);

    printf("bit count %d\n", countBits(block));
    int index = getLSBIndex(block);
    printf("LSB index %d\n", index);
    printBitboard(block);

    return 0;
}