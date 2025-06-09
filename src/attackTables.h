#ifndef attackTables
#define attackTables
#include <stdio.h>
#include "bit.h"
#include "randomizingRoutines.h"

<<<<<<< HEAD
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64];
extern U64 kingAttacks[64];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bishopAttacks[64][512];
extern U64 rookAttacks[64][4096];
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
uint64 pawnAttacks[2][64];
uint64 knightAttacks[64];
uint64 kingAttacks[64];
uint64 mBishopAttacks[64][512]; // 256K
uint64 mRookAttacks[64][4096];   // 2048K
>>>>>>> 62ee2dc8c871bba702002c27d05864cc29ba792d

int RBits[64];
int BBits[64];

typedef struct SMagic SMagic;
struct SMagic {
   uint64 mask;  // to mask relevant squares of both lines (no outer squares)
   uint64 magic; // magic 64-bit factor
};

SMagic mBishopTbl[64];
SMagic mRookTbl[64];

const uint64 NOT_A;
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

const uint64 NOT_B;
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

const uint64 NOT_H;
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
const uint64 NOT_G;
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

<<<<<<< HEAD
extern const U64 NOT_AB;
extern const U64 NOT_HG;
extern const U64 NOT_AH;
extern const U64 NOT_BH;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
const uint64 NOT_AB;
const uint64 NOT_HG;
const uint64 NOT_AH;
const uint64 NOT_BH;
>>>>>>> 62ee2dc8c871bba702002c27d05864cc29ba792d

int relevantBishopBits[64];
int relevantRookBits[64];

uint64 pmask(int side, int pos);    // masks for pawn attacks
uint64 nmask(int pos);              // mask for knight attacks
uint64 kmask(int pos);              // mask for king attacks
uint64 bmask(int pos);              // mask for bishop attacks
uint64 rmask(int pos);              // mask for rook attacks
uint64 batt(int pos, uint64 block); // generate bishop attacks on the fly
uint64 ratt(int pos, uint64 block); // generate rook attacks on the fly
uint64 setOccupancy(int index, int bitsInMask, uint64 attack_mask); // generates occupancy bitboard based on index
void initSliderAttacks();           // initializes bishop and rook attack tables to be used with magic numbers

// use these inline functions to get bishop and rook attacks
//  they use a magic number as a hash and run in constant time vs the generating functions above

<<<<<<< HEAD
>>>>>>> Stashed changes
=======

extern int relevantRookBitCounts[64];
extern int relevantBishopBitCounts[64];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bishopAttacks[64][512]; //256K
extern U64 rookAttacks[64][4096]; //2048K

>>>>>>> Stashed changes
=======

extern int relevantRookBitCounts[64];
extern int relevantBishopBitCounts[64];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bishopAttacks[64][512]; //256K
extern U64 rookAttacks[64][4096]; //2048K

>>>>>>> Stashed changes
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
=======
static inline uint64 bishopAttacks(uint64 occ, int sq){
    occ &= mBishopTbl[sq].mask; // mask out irrelevant squares
    occ *= mBishopTbl[sq].magic; // multiply by magic number
    occ >>= (64 - BBits[sq]); // shift to get the index
    return mBishopAttacks[sq][occ]; // return the precomputed attacks
}
static inline uint64 rookAttacks(uint64 occ, int sq){
    occ &= mRookTbl[sq].mask; // mask out irrelevant squares
    occ *= mRookTbl[sq].magic; // multiply by magic number
    occ >>= (64 - RBits[sq]); // shift to get the index
    return mRookAttacks[sq][occ]; // return the precomputed attacks 
>>>>>>> 62ee2dc8c871bba702002c27d05864cc29ba792d
}

void initAttackTables();            // initializes all the attack tables

#endif
