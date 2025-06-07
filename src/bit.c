#include <stdio.h>
#include <stdlib.h>

#include "bit.h"


void printBitboard(U64 bitboard) {
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
    printf("\n      Bitboard: %llud\n", bitboard);
<<<<<<< Updated upstream
=======
}
int bitScanForward(U64 bb) {
    if (bb == 0) return -1; 
    return __builtin_ctzll(bb); 
}
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
int bitScanForward(U64 bb) {
    if (bb == 0) return -1; 
    return __builtin_ctzll(bb); 
}
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
int countBits(U64 bitboard) {
    int count = 0;
    while (bitboard) {
        count++;
        bitboard &= (bitboard - 1);
    }
    return count;
}

int getLSBIndex(U64 bitboard) {
    if (bitboard == 0) return -1; // No bits set
    return __builtin_ctzll(bitboard); // Count trailing zeros
>>>>>>> Stashed changes
}