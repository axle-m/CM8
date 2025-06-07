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

uint64 bitboards[12] = { 
    0xff000000000000, 0x4200000000000000, 0x2400000000000000, 
    0x8100000000000000, 0x800000000000000, 0x1000000000000000,
    0xff00, 0x42, 0x24, 0x81, 0x8, 0x10
};

uint64 occupancies[3] = {
    0xffff000000000000, 0xffff, 0xffff00000000ffff
};
int side = white;
int enpassant = no_sq;
int castle = WK + WQ + BK + BQ;
const char *squareToCoords[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

char asciiPieces[12] ={
    'P', 'N', 'B', 'R', 'Q', 'K',
    'p', 'n', 'b', 'r', 'q', 'k'
};

int char_pieces[] = {
    [P] = P,
    [N] = N,
    [B] = B,
    [R] = R,
    [Q] = Q,
    [K] = K,
    [p] = p,
    [n] = n,
    [b] = b,
    [r] = r,
    [q] = q,
    [k] = k
};

void printBoard(){
    for(int rank = 0; rank < 8; rank++){
        printf("%d  ", 8 - rank);
        for(int file = 0; file < 8; file++){
            int sq = rank * 8 + file;
            char piece = '.';
            for(int pce = P; pce <= k; pce++){
                if(GET_BIT(bitboards[pce], sq)){
                    piece = asciiPieces[pce];
                    break;
                }
            }
            printf("%c ", piece);
        }
        printf("\n");
    }
    printf("\n   a b c d e f g h\n");
    printf("  Side:           %s\n", !side ? "w" : "b");
    printf("  En Passant:    %s\n", enpassant == no_sq ? "no" : squareToCoords[enpassant]);
    printf("  Castle:      %c%c%c%c\n", 
        castle & WK ? 'K' : '-',
        castle & WQ ? 'Q' : '-',
        castle & BK ? 'k' : '-',
        castle & BQ ? 'q' : '-'
    );

    printf("\n");
}