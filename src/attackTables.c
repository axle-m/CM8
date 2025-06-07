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

void init() {
    for (int i = 0; i < 64; i++)
    {
        pawnAttacks[white][i] = maskPawnAttacks(white, i);
        pawnAttacks[black][i] = maskPawnAttacks(black, i);
        knightAttacks[i] = maskKnightAttacks(i);
        kingAttacks[i] = maskKingAttacks(i);
    }
}

U64 getPawnAttacks(int isWhite, int square) {
    return pawnAttacks[isWhite ? white : black][square];
}

U64 getKnightAttacks(int square) {
    return knightAttacks[square];
}

U64 getQueenAttacks(int square, U64 blockers) {
    return getBishopAttacks(square, blockers) | getRookAttacks(square, blockers);
}