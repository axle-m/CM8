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

U64 maskPawnAttacks(int side, int pos) {
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

void initPawnAttacks() {
    for(int i = 0; i < 64; i++) {
        pawnAttacks[white][i] = maskPawnAttacks(white, i);
        pawnAttacks[black][i] = maskPawnAttacks(white, i);
    }
}

U64 knightAttacks[2][64];

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

void initKnightAttacks() {
    for(int i = 0; i < 64; i++) {
        U64 mask = maskKnightAttacks(i);
        knightAttacks[white][i] = mask;
        knightAttacks[black][i] = mask;
        printf("Knight attacks for %d: %llud\n", i, mask);
        printBitboard(mask);
    }
}