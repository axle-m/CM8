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
}