#include <stdio.h>
#include "bit.h"

<<<<<<< Updated upstream
U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];
=======
extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64];
extern U64 kingAttacks[64];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bishopAttacks[64][512];
extern U64 rookAttacks[64][4096];
>>>>>>> Stashed changes

extern const U64 NOT_A;
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

extern const U64 NOT_B;
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

extern const U64 NOT_H;
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
extern const U64 NOT_G;
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

extern const U64 NOT_AB;
extern const U64 NOT_HG;
extern const U64 NOT_AH;
extern const U64 NOT_BH;

<<<<<<< Updated upstream
U64 maskPawnAttacks(int side, int pos);
U64 maskKnightAttacks(int pos);
U64 maskKingAttacks(int pos);
U64 maskBishopAttacks(int pos);
U64 maskRookAttacks(int pos);
void init();
=======
extern int relevantRookBitCounts[64];
extern int relevantBishopBitCounts[64];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bishopAttacks[64][512]; //256K
extern U64 rookAttacks[64][4096]; //2048K

extern U64 maskPawnAttacks(int side, int pos);
extern U64 maskKnightAttacks(int pos);
extern U64 maskKingAttacks(int pos);
extern U64 maskBishopAttacks(int pos);
extern U64 maskRookAttacks(int pos);
extern U64 genBishopAttacks(int pos, U64 block);
extern U64 genRookAttacks(int pos, U64 block);
extern U64 setOccupancy(int index, int bitsInMask, U64 attack_mask);
extern U64 initSliderAttacks(int bishop /*1 for bishop, 0 for rook*/);

static inline U64 getBishopAttacks(U64 occ, int sq) {
    printf("mask:\n");
    printBitboard(bishopMasks[sq]);
    printf("\nmagic: %llx\n", BISHOP_MAGICS[sq]);

    occ &= bishopMasks[sq];
    int index = (occ * BISHOP_MAGICS[sq]) >> (64 - relevantBishopBitCounts[sq]);
    return bishopAttacks[sq][index];
}

static inline U64 getRookAttacks(U64 occ, int sq) {
    printf("mask:\n");
    printBitboard(rookMasks[sq]);
    printf("\nmagic: %llx\n", ROOK_MAGICS[sq]);
    occ &= rookMasks[sq];
    int index = (occ * ROOK_MAGICS[sq]) >> (64 - relevantRookBitCounts[sq]);
    return rookAttacks[sq][index];
}

void initAttackTables();
U64 getPawnAttacks(int isWhite, int square);
U64 getKnightAttacks(int square);
U64 getQueenAttacks(int square, U64 blockers);

void initAll();
#endif
>>>>>>> Stashed changes
