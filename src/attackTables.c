#include <stdio.h>
#include <stdlib.h>

#include "bit.h"
#include "attackTables.h"
#include "randomizingRoutines.h"

const uint64 NOT_A = 18374403900871474942ULL;
const uint64 NOT_B = 18302063728033398269ULL;
const uint64 NOT_H = 9187201950435737471ULL; 
const uint64 NOT_G = 13816973012072644543ULL;
const uint64 NOT_AB = 18229723555195321596ULL;
const uint64 NOT_HG = 4557430888798830399ULL;

uint64 pawnAttacks [2][64];
uint64 knightAttacks[64];
uint64 kingAttacks[64];

uint64 mBishopAttacks[64][512]; // 256K
uint64 mRookAttacks[64][4096];   // 2048K

SMagic mBishopTbl[64];
SMagic mRookTbl[64];

int BBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6,
};

int RBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12,
};

uint64 pmask(int side, int pos) {
    uint64 bitboard = 0ULL;
    uint64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    if(!side) { //white
        mask |= ((bitboard >> 7) & NOT_A) | ((bitboard >> 9) & NOT_H);
    } else { //black
        mask |= ((bitboard << 7) & NOT_H) | ((bitboard << 9) & NOT_A);;
    }

    return mask;
}

uint64 nmask(int pos) {
    uint64 bitboard = 0ULL;
    uint64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    mask |= ((bitboard >> 15) & NOT_A) | ((bitboard >> 17) & NOT_H);
    mask |= ((bitboard >> 6) & NOT_AB) | ((bitboard >> 10) & NOT_HG);
    mask |= ((bitboard << 15) & NOT_H) | ((bitboard << 17) & NOT_A);
    mask |= ((bitboard << 6) & NOT_HG) | ((bitboard << 10) & NOT_AB);
    
    return mask;
}

uint64 kmask(int pos) {
    uint64 bitboard = 0ULL;
    uint64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    mask |= bitboard >> 8;
    mask |= bitboard << 8;
    mask |= ((bitboard >> 1) & NOT_H);
    mask |= ((bitboard << 1) & NOT_A);
    mask |= ((bitboard >> 7) & NOT_A);
    mask |= ((bitboard << 7) & NOT_H);
    mask |= ((bitboard >> 9) & NOT_H);
    mask |= ((bitboard << 9) & NOT_A);

    return mask;
}

uint64 bmask(int sq) {
    uint64 result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r=rk+1, f=fl+1; r<=6 && f<=6; r++, f++) result |= (1ULL << (f + r*8));
    for(r=rk+1, f=fl-1; r<=6 && f>=1; r++, f--) result |= (1ULL << (f + r*8));
    for(r=rk-1, f=fl+1; r>=1 && f<=6; r--, f++) result |= (1ULL << (f + r*8));
    for(r=rk-1, f=fl-1; r>=1 && f>=1; r--, f--) result |= (1ULL << (f + r*8));
    return result;
}

uint64 rmask(int sq) {
    uint64 result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r = rk+1; r <= 6; r++) result |= (1ULL << (fl + r*8));
    for(r = rk-1; r >= 1; r--) result |= (1ULL << (fl + r*8));
    for(f = fl+1; f <= 6; f++) result |= (1ULL << (f + rk*8));
    for(f = fl-1; f >= 1; f--) result |= (1ULL << (f + rk*8));
    return result;
}

uint64 batt(int pos, uint64 block) {
    uint64 result = 0ULL;
    int rk = pos/8, fl = pos%8, r, f;
    for(r = rk+1, f = fl+1; r <= 7 && f <= 7; r++, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk+1, f = fl-1; r <= 7 && f >= 0; r++, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl+1; r >= 0 && f <= 7; r--, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl-1; r >= 0 && f >= 0; r--, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    return result;
}

uint64 ratt(int pos, uint64 block) {
    uint64 result = 0ULL;
    int rk = pos/8, fl = pos%8, r, f;
    for(r = rk+1; r <= 7; r++) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }
    for(r = rk-1; r >= 0; r--) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }
    for(f = fl+1; f <= 7; f++) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }
    for(f = fl-1; f >= 0; f--) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }
    return result;
}

uint64 setOccupancy(int index, int bitsInMask, uint64 attackMask) {
    uint64 occupancy = 0ULL;
    int count = 0;

    while (attackMask) {
        int square = getLSBIndex(attackMask);
        attackMask &= attackMask - 1;  // clear the LSB
        if (index & (1 << count)) {
            occupancy |= (1ULL << square);
        }
        count++;
    }
    return occupancy;
}

void initSliderAttacks() {
    // printf("Initializing slider attacks...\n");
    for (int square = 0; square < 64; square++) {
        //Bishop
        mBishopTbl[square].mask = bmask(square);
        mBishopTbl[square].magic = BMagic[square];
        uint64 bishopMask = mBishopTbl[square].mask;
        int bishopBits = BBits[square];
        int bishopSize = 1 << bishopBits;

        for (int index = 0; index < bishopSize; index++) {
            uint64 occupancy = setOccupancy(index, bishopBits, mBishopTbl[square].mask);
            int mIndex = (occupancy * mBishopTbl[square].magic) >> (64 - bishopBits);
            mBishopAttacks[square][mIndex] = batt(square, occupancy);
        }

        // Rook
        mRookTbl[square].mask = rmask(square);
        mRookTbl[square].magic = RMagic[square];
        uint64 rookMask = mRookTbl[square].mask;
        int rookBits = RBits[square];
        int rookSize = 1 << rookBits;

        for (int index = 0; index < rookSize; index++) {
            uint64 occupancy = setOccupancy(index, rookBits, rookMask);
            int mIndex = (occupancy * mRookTbl[square].magic) >> (64 - rookBits);
            mRookAttacks[square][mIndex] = ratt(square, occupancy);
        }
    }
    // printf("Slider attacks initialized.\n");
}

void initAttackTables() {
    // printf("Initializing attack tables...\n");
    for (int i = 0; i < 64; i++)
    {
        pawnAttacks[white][i] = pmask(white, i);
        pawnAttacks[black][i] = pmask(black, i);
        knightAttacks[i] = nmask(i);
        kingAttacks[i] = kmask(i);
    }
    initSliderAttacks();
    // printf("Attack tables initialized.\n");
}