#include <stdio.h>
#include <stdlib.h>

#include "bit.h"
#include "attackTables.h"

#include "attackTables.h"

const U64 NOT_A = 18374403900871474942ULL;
const U64 NOT_B = 13203522227539424382ULL;
const U64 NOT_H = 9187201950435737471ULL;
const U64 NOT_G = 17293822569102704640ULL;

U64 pawnAttacks [2][64];

U64 maskPawnAttacks(int pos, int side) {
    U64 bitboard = 0ULL;
    U64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    printf("%d", side);

    if(!side) { //white
        mask |= ((bitboard >> 7) & NOT_A) | ((bitboard >> 9) & NOT_H);
    } else { //black
        mask |= ((bitboard << 7) & NOT_H) | ((bitboard << 9) & NOT_A);;
    }
    return mask;
}