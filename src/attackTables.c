#include <stdio.h>
#include <stdlib.h>

#include "bit.h"
#include "attackTables.h"

const U64 NOT_A = 18374403900871474942ULL;
const U64 NOT_B = 18302063728033398269ULL;
const U64 NOT_H = 9187201950435737471ULL; 
const U64 NOT_G = 13816973012072644543ULL;
const U64 NOT_AB = 18229723555195321596ULL;
const U64 NOT_HG = 4557430888798830399ULL;

U64 pawnAttacks [2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];

U64 maskPawnAttacks(int side, int pos) {
    U64 bitboard = 0ULL;
    U64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    if(!side) { //white
        mask |= ((bitboard >> 7) & NOT_A) | ((bitboard >> 9) & NOT_H);
    } else { //black
        mask |= ((bitboard << 7) & NOT_H) | ((bitboard << 9) & NOT_A);;
    }

    return mask;
}

U64 maskKnightAttacks(int pos) {
    U64 bitboard = 0ULL;
    U64 mask = 0ULL;

    SET_BIT(bitboard, pos);

    mask |= ((bitboard >> 15) & NOT_A) | ((bitboard >> 17) & NOT_H);
    mask |= ((bitboard >> 6) & NOT_AB) | ((bitboard >> 10) & NOT_HG);
    mask |= ((bitboard << 15) & NOT_H) | ((bitboard << 17) & NOT_A);
    mask |= ((bitboard << 6) & NOT_HG) | ((bitboard << 10) & NOT_AB);
    
    return mask;
}

U64 maskKingAttacks(int pos) {
    U64 bitboard = 0ULL;
    U64 mask = 0ULL;

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

U64 maskBishopAttacks(int pos) {
    U64 mask = 0ULL;

    int r, f;
    int tr = pos / 8, tf = pos % 8;

    for(r = tr + 1, f = tf + 1; r < 7 && f < 7; r++, f++) {
        mask |= (1ULL << (r * 8 + f));
    }
    for(r = tr + 1, f = tf - 1; r < 7 && f > 0; r++, f--) {
        mask |= (1ULL << (r * 8 + f));
    }
    for(r = tr - 1, f = tf + 1; r > 0 && f < 7; r--, f++) {
        mask |= (1ULL << (r * 8 + f));
    }
    for(r = tr - 1, f = tf - 1; r > 0 && f > 0; r--, f--) {
        mask |= (1ULL << (r * 8 + f));
    }

    return mask;
}

U64 maskRookAttacks(int pos) {
    U64 mask = 0ULL;

    int r, f;
    int tr = pos / 8, tf = pos % 8;

    for(r = tr + 1; r < 7; r++) {
        mask |= (1ULL << (r * 8 + tf));
    }
    for(r = tr - 1; r > 0; r--) {
        mask |= (1ULL << (r * 8 + tf));
    }
    for(f = tf + 1; f < 7; f++) {
        mask |= (1ULL << (tr * 8 + f));
    }
    for(f = tf - 1; f > 0; f--) {
        mask |= (1ULL << (tr * 8 + f));
    }

    return mask;
}

U64 genBishopAttacks(int pos, U64 block) {
    U64 mask = 0ULL;
    U64 bitboard = 0ULL;
    SET_BIT(bitboard, pos);

    int r, f;
    int tr = pos / 8, tf = pos % 8;

    for(r = tr + 1, f = tf + 1; r < 8 && f < 8; r++, f++) {
        mask |= (1ULL << (r * 8 + f));
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(r = tr + 1, f = tf - 1; r < 8 && f >= 0; r++, f--) {
        mask |= (1ULL << (r * 8 + f));
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(r = tr - 1, f = tf + 1; r >= 0 && f < 8; r--, f++) {
        mask |= (1ULL << (r * 8 + f));
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        mask |= (1ULL << (r * 8 + f));
        if((1ULL << (r * 8 + f)) & block) break;
    }

    block = bitboard & mask;

    return mask;
}

U64 genRookAttacks(int pos, U64 block) {
    U64 mask = 0ULL;
    U64 bitboard = 0ULL;
    SET_BIT(bitboard, pos);

    int r, f;
    int tr = pos / 8, tf = pos % 8;

    for(r = tr + 1; r < 8; r++) {
        mask |= (1ULL << (r * 8 + tf));
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for(r = tr - 1; r >= 0; r--) {
        mask |= (1ULL << (r * 8 + tf));
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for(f = tf + 1; f < 8; f++) {
        mask |= (1ULL << (tr * 8 + f));
        if((1ULL << (tr * 8 + f)) & block) break;
    }
    for(f = tf - 1; f >= 0; f--) {
        mask |= (1ULL << (tr * 8 + f));
        if((1ULL << (tr * 8 + f)) & block) break;
    }

    block = bitboard & mask;

    return mask;
}

void init() {
    for (int i = 0; i < 64; i++)
    {
        pawnAttacks[white][i] = maskPawnAttacks(white, i);
        pawnAttacks[black][i] = maskPawnAttacks(black, i);
        knightAttacks[i] = maskKnightAttacks(i);
        kingAttacks[i] = maskKingAttacks(i);
    }
}