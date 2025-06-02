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

    U64 mask = maskRookAttacks(a1);
    printBitboard(mask);

    printf("LSB index: %d\n", getLSBIndex(mask));

    U64 occupancy = setOccupancy(4095, countBits(mask), mask);

    printBitboard(occupancy);

    return 0;
}