#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    printf("Testing random blocker configurations\n");
    int errors = 0;
    for(int i = 0; i < 4294967296; i++) {
        uint64 blocker = randomuint64fewbits();
        int pos = getrand64() % 64;

        uint64 generatedAttacks = batt(pos, blocker) | ratt(pos, blocker);
        uint64 lookupAttacks = queenAttacks(blocker, pos);

        if(i % 1000000 == 0) {
            printf("Tested %d configurations, found %d errors\n", i, errors);
        }

        if(generatedAttacks != lookupAttacks) {
            printf("Mismatch found!\n");
            printf("Position: %d\n", pos);
            printf("Blocker: \n");
            printBitboard(blocker);
            printf("Generated Attacks: \n");
            printBitboard(generatedAttacks);
            printf("Lookup Attacks: \n");
            printBitboard(lookupAttacks);
            errors++;
            if(errors > 10) {
                printf("Too many errors, stopping test.\n");
                break;
            }
        }
    }
    printf("Testing completed with %d errors found\n", errors);


    cleanup();
    return 0;
}