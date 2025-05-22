#include <stdio.h>

#include "bit.h"
#include "attackTables.h"

int main() {
    printf("cm8 engine\n");

    U64 bitboard = 0ULL;

    SET_BIT(bitboard, e4);

    initKnightAttacks();

    return 0;
}