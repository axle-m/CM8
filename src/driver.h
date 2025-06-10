#ifndef driver
#define driver
#include <stdio.h>
#include <windows.h>
//include other headers for cleaner main file

#include "bit.h"
#include "attackTables.h"
#include "randomizingRoutines.h"
#include "inputProcessor.h"
#include "moveGenerator.h"

int getBestMove();
void oneVsOne();
void init();
void cleanup();
uint64 unix_time_ms();

int materialScores[12];
const int pawnScore[64];
const int knightScore[64];
const int rookScore[64];
const int kingScore[64];
const int bishopScore[64];
const int kingScore[64];
const int mirrorScore[128];

static inline int evaluate() {
    int score = 0;
    uint64 bb;
    int piece, pos;

    for(int pce = P; pce <= k; pce++) {
        bb = bitboards[pce];
        while(bb) {
            pos = pop_1st_bit(&bb);
            score += materialScores[pce];
            switch(pce) {
                case P: score += pawnScore[pos]; break;
                case N: score += knightScore[pos]; break;
                case B: score += bishopScore[pos]; break;
                case R: score += rookScore[pos]; break;
                case K: score += kingScore[pos]; break;

                case p: score -= pawnScore[mirrorScore[pos]]; break;
                case n: score -= knightScore[mirrorScore[pos]]; break;
                case b: score -= bishopScore[mirrorScore[pos]]; break;
                case r: score -= rookScore[mirrorScore[pos]]; break;
                case k: score -= kingScore[mirrorScore[pos]]; break;
                
                default: break;
            }
        }
    }


    return score * (side == white ? 1 : -1);
}

#endif