#include <stdio.h>
#include "bit.h"

unsigned int RANDOM_STATE;
const U64 ROOK_MAGICS[64];
const U64 BISHOP_MAGICS[64];

unsigned int getrand32();
U64 getrand64();
U64 randomU64fewbits();
int pop1st(U64 *bb);
U64 indexToU64(int index, int bits, U64 m);
U64 findMagic(int square, int relevantBits, int bishop);
int transform(U64 b, U64 magic, int bits);
void initMagicNumbers();
void initRandomizingRoutines();