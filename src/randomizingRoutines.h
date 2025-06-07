#ifndef randomizingRoutines
#define randomizingRoutines
#include <stdio.h>
#include "bit.h"

unsigned int RANDOM_STATE;
const uint64 RMagic[64];
const uint64 BMagic[64];

unsigned int getrand32();               // returns pseudo-random 32-bit unsigned integer based on the random state using the XOR shift algorithm
uint64 getrand64();                     // returns a pseudo-random 64-bit unsigned integer by combining 4 calls to getRand32
uint64 randomuint64fewbits();           // returns a pseudo-random 64-bit unsigned integer with a fewer bits set than getRand64
int pop1st(uint64 *bb);                 // pops and returns the index of the least significant bit that is set to 1
uint64 findMagic(int square, int relevantBits, int bishop); // finds the magic number for a given square and piece type (rook or bishop)
int transform(uint64 b, uint64 magic, int bits);    // transforms the bitboard using the magic number and returns the index for the attack table
void initMagicNumbers();                // initializes the magic numbers for rooks and bishops
void initRandomizingRoutines();         // initializes the random state and magic numbers by a call to initMagicNumbers();
#endif