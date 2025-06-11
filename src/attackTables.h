#ifndef attackTables
#define attackTables
#include <stdio.h>
#include "bit.h"
#include "randomizingRoutines.h"

extern uint64 pawnAttacks[2][64];
extern uint64 knightAttacks[64];
extern uint64 kingAttacks[64];
extern uint64 mBishopAttacks[64][512]; // 256K
extern uint64 mRookAttacks[64][4096];   // 2048K

extern int RBits[64];
extern int BBits[64];

typedef struct SMagic SMagic;
struct SMagic {
   uint64 mask;  // to mask relevant squares of both lines (no outer squares)
   uint64 magic; // magic 64-bit factor
};

extern SMagic mBishopTbl[64];
extern SMagic mRookTbl[64];

extern const uint64 NOT_A;
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

extern const uint64 NOT_B;
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

extern const uint64 NOT_H;
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
extern const uint64 NOT_G;
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

extern const uint64 NOT_AB;
extern const uint64 NOT_HG;
extern const uint64 NOT_AH;
extern const uint64 NOT_BH;

extern int relevantBishopBits[64];
extern int relevantRookBits[64];

extern uint64 pmask(int side, int pos);    // masks for pawn attacks
extern uint64 nmask(int pos);              // mask for knight attacks
extern uint64 kmask(int pos);              // mask for king attacks
extern uint64 bmask(int pos);              // mask for bishop attacks
extern uint64 rmask(int pos);              // mask for rook attacks
extern uint64 batt(int pos, uint64 block); // generate bishop attacks on the fly
extern uint64 ratt(int pos, uint64 block); // generate rook attacks on the fly
extern uint64 setOccupancy(int index, int bitsInMask, uint64 attack_mask); // generates occupancy bitboard based on index
void initSliderAttacks();           // initializes bishop and rook attack tables to be used with magic numbers

// use these inline functions to get bishop and rook attacks
//  they use a magic number as a hash and run in constant time vs the generating functions above

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
}
static inline uint64 queenAttacks(uint64 occ, int sq){
    return bishopAttacks(occ, sq) | rookAttacks(occ, sq); // return the precomputed attacks
}

void initAttackTables(); // initializes all the attack tables

#endif