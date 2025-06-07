#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    uint64 bb = 0ULL;
    SET_BIT(bb, e3);
    SET_BIT(bb, b7);
    SET_BIT(bb, d3);

    printf("Initial bitboard:\n");
    printBitboard(bb);

    printf("bishop attacks from e4:\n");
    printBitboard(bishopAttacks(bb, e4));
    printf("rook attacks from e4:\n");
    printBitboard(rookAttacks(bb, e4));

    cleanup();
    return 0;
}