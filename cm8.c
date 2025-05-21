#include <stdio.h>

#include "bit.h"
#include "attackTables.h"

int main() {
    printf("cm8 engine\n");

    U64 bitboard = 0ULL;

    initPawnAttacks();
    for(int i = 0; i < 64; i++) {
        printf("white pawn attack %d: ", i);
        printBitboard(pawnAttacks[white][i]);
        printf("black pawn attack %d: ", i);
        printBitboard(pawnAttacks[black][i]);
    }

    return 0;
}