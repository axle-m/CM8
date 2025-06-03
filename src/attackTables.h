#include <stdio.h>
#include "bit.h"

U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];

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

const int relevantBishopBits[64];
const int relevantRookBits[64];

U64 maskPawnAttacks(int side, int pos);
U64 maskKnightAttacks(int pos);
U64 maskKingAttacks(int pos);
U64 maskBishopAttacks(int pos);
U64 maskRookAttacks(int pos);
U64 genBishopAttacks(int pos, U64 block);
U64 genRookAttacks(int pos, U64 block);
U64 setOccupancy(int index, int bitsInMask, U64 attack_mask);
void init();
