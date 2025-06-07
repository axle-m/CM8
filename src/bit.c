#include <stdio.h>
#include <stdlib.h>

#include "bit.h"

void printBitboard(uint64 bitboard) {
    for(int i = 0; i < 64; i++) {

        //print ranks
        if (i % 8 == 0) {
            printf("\n%d    ", 8 - (i / 8));
        }

        //print bit
        printf("%d ", GET_BIT(bitboard, i));
    }
    printf("\n\n     a b c d e f g h\n");

    //print bitboard as unsigned decimal
    printf("\n      Bitboard: %llu\n", bitboard);
}

int countBits(uint64 bitboard) {
    int count = 0;
    while (bitboard) {
        count++;
        bitboard &= (bitboard - 1);
    }
    return count;
}

int count_1s(uint64 b) {
    int r;
    for(r = 0; b; r++, b &= b - 1);
    return r;
}

int getLSBIndex(uint64 bitboard) {
    if (bitboard == 0) return -1; // No bits set
    return __builtin_ctzll(bitboard); // Count trailing zeros
}

const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

int pop_1st_bit(uint64 *bb) {
    uint64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}


uint64 index_to_uint64(int index, int bits, uint64 m) {
    int i, j;
    uint64 result = 0ULL;
    for(i = 0; i < bits; i++) {
        j = pop_1st_bit(&m);
        if(index & (1 << i)) result |= (1ULL << j);
        }
    return result;
}