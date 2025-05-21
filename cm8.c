#include <stdio.h>

#include "bit.h"
#include "attackTables.h"

int main() {
    printf("cm8 engine\n");

    U64 bitboard = 0ULL;
    SET_BIT(bitboard, h4);

    printBitboard(maskPawnAttacks(h4, black));
    return 0;
}