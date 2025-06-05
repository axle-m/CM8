/*
    * This file contains functions for generating random numbers and magic numbers
    * for bitboard attacks
    *
    * The brute-force approach to finding magics is proposed by Tord Romstad
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define USE_32_BIT_MULTIPLICATIONS

#include "bit.h"
#include "attackTables.h"
#include "randomizingRoutines.h"

unsigned int RANDOM_STATE = 1804289383;

const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

unsigned int getrand32() {
    unsigned int x = RANDOM_STATE;

    //XOR shift algorithm
    x ^= (x << 13);
    x ^= (x >> 17);
    x ^= (x << 5);
    RANDOM_STATE = x;
    return x;
}

U64 getrand64() {
    U64 a, b, c, d;
    a = (U64)(getrand32()) & 0xFFFF;
    b = (U64)(getrand32()) & 0xFFFF;
    c = (U64)(getrand32()) & 0xFFFF;
    d = (U64)(getrand32()) & 0xFFFF;

    return a | (b << 16) | (c << 32) | (d << 48);
}

U64 randomU64fewbits() {
  return getrand64() & getrand64() & getrand64();
}

int pop1st(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

U64 indexToU64(int index, int bits, U64 m) {
    int i, j;
    U64 result = 0ULL;
    for(i = 0; i < bits; i++) {
        j = pop1st(&m);
        if(index & (1 << i)) result |= (1ULL << j);
    }
    return result;
}

int transform(U64 b, U64 magic, int bits) {
#if defined(USE_32_BIT_MULTIPLICATIONS)
    return (unsigned)((int)b*(int)magic ^ (int)(b>>32)*(int)(magic>>32)) >> (32-bits);
#else
  return (int)((b * magic) >> (64 - bits));
#endif
}

U64 findMagic(int square, int relevantBits, int bishop) {
    U64 mask, b[4096], a[4096], used[4096], magic;
    int i, j, k, n, fail;

    mask = bishop? maskBishopAttacks(square) : maskRookAttacks(square);
    n = countBits(mask);

    for(i = 0; i < (1 << n); i++) {
        b[i] = indexToU64(i, n, mask);
        a[i] = bishop? genBishopAttacks(square, b[i]) : genRookAttacks(square, b[i]);
    }
    for(k = 0; k < 100000000; k++) {
        magic = randomU64fewbits();
        if(countBits((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
        for(i = 0; i < 4096; i++) used[i] = 0ULL;
        for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
            j = transform(b[i], magic, relevantBits);
            if(used[j] == 0ULL) used[j] = a[i];
            else if(used[j] != a[i]) fail = 1;
        }
        if(!fail) return magic;
    }
    printf("***Failed***\n");
    return 0ULL;
}

void initMagicNumbers() {
    printf("Rook Magics:\n");
    for(int i = 0; i < 64; i++){
        printf(" 0x%lluxULL\n", findMagic(i, relevantRookBits[i], rook));
    }
    printf("\nBishop Magics:\n");
    for(int i = 0; i < 64; i++){
        printf(" 0x%lluxULL\n", findMagic(i, relevantBishopBits[i], bishop));
    }
}

void initRandomizingRoutines() {
    RANDOM_STATE = 1804289383; // Reset the random state
    initMagicNumbers();
}

