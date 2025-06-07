#ifndef randomizingRoutines
#define randomizingRoutines
#include <stdio.h>
#include "bit.h"

unsigned int RANDOM_STATE;
const uint64 RMagic[64];
const uint64 BMagic[64];

unsigned int getrand32();
uint64 getrand64();
uint64 randomuint64fewbits();
int pop1st(uint64 *bb);
uint64 indexTouint64(int index, int bits, uint64 m);
uint64 findMagic(int square, int relevantBits, int bishop);
int transform(uint64 b, uint64 magic, int bits);
void initMagicNumbers();
void initRandomizingRoutines();
#endif