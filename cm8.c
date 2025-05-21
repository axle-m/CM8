#include <stdio.h>

#include "bit.h"

int main() {
    printf("cm8 engine\n");

    U64 bitboard = 0ULL;  // Example bitboard
    printBitboard(bitboard);
    SET_BIT(bitboard, a8);
    printBitboard(bitboard);
    printf("Bit at a8: %d\n", GET_BIT(bitboard, a8));
    return 0;
}