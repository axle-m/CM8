#include <stdio.h>
#include "bit.h"
#include "randomizingRoutines.h"

U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];
U64 bishopMasks[64];
U64 rookMasks[64];
U64 bishopAttacks[64][512];
U64 rookAttacks[64][4096];

const U64 NOT_A;
/* not A
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
*/

const U64 NOT_B;
/* not B
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
*/

const U64 NOT_H;
/* not H
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
*/
const U64 NOT_G;
/* not G
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
*/

const U64 NOT_AB;
const U64 NOT_HG;
const U64 NOT_AH;
const U64 NOT_BH;

int relevantBishopBits[64];
int relevantRookBits[64];
U64 bishopMasks[64];
U64 rookMasks[64];
U64 bishopAttacks[64][512];
U64 rookAttacks[64][4096];

U64 maskPawnAttacks(int side, int pos);
U64 maskKnightAttacks(int pos);
U64 maskKingAttacks(int pos);
U64 maskBishopAttacks(int pos);
U64 maskRookAttacks(int pos);
U64 genBishopAttacks(int pos, U64 block);
U64 genRookAttacks(int pos, U64 block);
U64 setOccupancy(int index, int bitsInMask, U64 attack_mask);
U64 initSliderAttacks(int bishop /*1 for bishop, 0 for rook*/);
static inline U64 getBishopAttacks(int square, U64 occupancy) {
    int magicIndex = (occupancy * BISHOP_MAGICS[square]) >> (64 - relevantBishopBits[square]);
    return bishopAttacks[square][magicIndex];
}

void initAttackTables();
