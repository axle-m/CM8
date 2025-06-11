#ifndef randomizingRoutines
#define randomizingRoutines
#include <stdio.h>
#include "bit.h"

extern unsigned int RANDOM_STATE;
extern const uint64 RMagic[64];
extern const uint64 BMagic[64];

extern unsigned int getrand32();               // returns pseudo-random 32-bit unsigned integer based on the random state using the XOR shift algorithm
extern uint64 getrand64();                     // returns a pseudo-random 64-bit unsigned integer by combining 4 calls to getRand32
extern uint64 randomuint64fewbits();           // returns a pseudo-random 64-bit unsigned integer with a fewer bits set than getRand64
extern int pop1st(uint64 *bb);                 // pops and returns the index of the least significant bit that is set to 1
extern uint64 findMagic(int square, int relevantBits, int bishop); // finds the magic number for a given square and piece type (rook or bishop)
extern int transform(uint64 b, uint64 magic, int bits);    // transforms the bitboard using the magic number and returns the index for the attack table
extern void initMagicNumbers();                // initializes the magic numbers for rooks and bishops
extern void initRandomizingRoutines();         // initializes the random state and magic numbers by a call to initMagicNumbers();
#endif