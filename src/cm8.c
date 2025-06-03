#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bit.h"
#include "attackTables.h"
#include "inputProcessor.h"
#include "randomizingRoutines.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    printBitboard((U64)getrand32());
    printBitboard((U64)getrand32() & 0xFFFF);
    printBitboard(getrand64());
    printBitboard(genmagic());

    return 0;
}