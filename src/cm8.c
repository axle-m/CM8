#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bit.h"
#include "attackTables.h"
#include "inputProcessor.h"
#include "randomizingRoutines.h"
#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    U64 bitboard = 0ULL;
    printBitboard(bitboard);
    SET_BIT(bitboard, d3);
    printBitboard(bitboard);

    printBitboard(getBishopAttacks(bitboard, e4));
    cleanup();
    return 0;
}