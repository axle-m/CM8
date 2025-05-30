#include <stdio.h>
#include <string.h>

#include "bit.h"
#include "attackTables.h"
#include "inputProcessor.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    U64 bitboard = 0ULL;

    bitboard = maskBishopAttacks(e4);

    printBitboard(bitboard);



    return 0;
} 