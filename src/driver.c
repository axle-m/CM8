#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"

int getBestMove(){
    return 0;
}

void init() {
    initAttackTables();
    initRandomizingRoutines();
}

void cleanup(){
    // for(int i = 0; i < 64; i++) {
    //     free(mBishopTable[i]);
    //     free(mRookTable[i]);
    // }
    // printf("Cleanup done.\n");
}

uint64 unix_time_ms() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64 t = ((uint64)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    // FILETIME is in 100-nanosecond intervals since Jan 1, 1601
    // Convert to milliseconds since Unix epoch (Jan 1, 1970)
    return (t - 116444736000000000ULL) / 10000ULL;
}
