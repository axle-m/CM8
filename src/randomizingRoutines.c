/*
    * This file contains functions for generating random numbers and magic numbers
    * for bitboard attacks
    *
    * This brute-force approach to finding magics is proposed by Tord Romstad
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define USE_32_BIT_MULTIPLICATIONS

#include "driver.h"
//1804289383
unsigned int RANDOM_STATE = 2309857210;
                            
const uint64 RMagic[64] = {
    0x408000f2804008a0ULL,
    0x10c0004010006002ULL,
    0x200102200088040ULL,
    0x9100200408100100ULL,
    0x600341008060060ULL,
    0x2200081004010200ULL,
    0x1500048406000100ULL,
    0x180122241000080ULL,
    0x4390802040008000ULL,
    0x1002100400080ULL,
    0x400801000802000ULL,
    0x801000080080ULL,
    0x1001208000500ULL,
    0x284808004002200ULL,
    0x4005084080102ULL,
    0x4002000041062884ULL,
    0xa088808000304000ULL,
    0x600808020004000ULL,
    0x610008010200880ULL,
    0x90010002100ULL,
    0x1008008008040080ULL,
    0x4008080040200ULL,
    0x300040001080210ULL,
    0x2510020000804401ULL,
    0x240004a80058c20ULL,
    0x10004040002000ULL,
    0x4420100080200084ULL,
    0x2021000900100022ULL,
    0x80080800400ULL,
    0x1085840080020080ULL,
    0x2000700400228108ULL,
    0x9104009200111044ULL,
    0x1c00400080800020ULL,
    0x1060804008802008ULL,
    0x40200084801000ULL,
    0x280100080800800ULL,
    0x8204008044804800ULL,
    0xc0800400800200ULL,
    0x400014204009008ULL,
    0x80028702001444ULL,
    0x10800040a001c010ULL,
    0x4c0002810002001ULL,
    0x2181006000c30030ULL,
    0x100008008080ULL,
    0xc018000400808008ULL,
    0x80041020080140ULL,
    0x4000011002040008ULL,
    0x4200284144a0001ULL,
    0x90800020510300ULL,
    0x400200040100040ULL,
    0x480410018200100ULL,
    0xc8000810008080ULL,
    0x808010010840900ULL,
    0x76000894101200ULL,
    0x8850015048024400ULL,
    0x84431c0200ULL,
    0x1040800100102041ULL,
    0x200884000110021ULL,
    0x3000941200411ULL,
    0x212002040040812ULL,
    0x1001002080005ULL,
    0x3001000400020801ULL,
    0x51000400820021ULL,
    0x200a4c4050286ULL,
};

const uint64 BMagic[64] = {
    0x4088200104003080ULL,
    0x201a040c50820008ULL,
    0x4010109224400008ULL,
    0x802208600100000ULL,
    0x1104000000020ULL,
    0x22009004a0010040ULL,
    0x82088405408020ULL,
    0x8900804800846000ULL,
    0x413400882040044ULL,
    0x100b80104109200ULL,
    0x110220a2c062000ULL,
    0x18000c2410808210ULL,
    0x100040422080000ULL,
    0x4000110420043611ULL,
    0x9801040108923000ULL,
    0x862082282000ULL,
    0x40a0024089322090ULL,
    0x5204208808882440ULL,
    0x8040002042a0200ULL,
    0x80080c0082004100ULL,
    0x4806400a00298ULL,
    0x40480010090c001ULL,
    0x20040200a4040299ULL,
    0x802010084908800ULL,
    0x820052210100220ULL,
    0xd0c2018284800ULL,
    0x4704008a440400ULL,
    0x5004040000410200ULL,
    0x2210100e0104000ULL,
    0x105020083008084ULL,
    0xa160821024010400ULL,
    0x5c004029010098ULL,
    0x101084002081004ULL,
    0x1040842098100200ULL,
    0x44020104020410ULL,
    0x100020080180080ULL,
    0x404040040100ULL,
    0x10c08600210100ULL,
    0x10040104006100ULL,
    0x14340020045100ULL,
    0x8014222110100402ULL,
    0x820440460010400ULL,
    0x2101804002810ULL,
    0x200002024242804ULL,
    0x800422009000202ULL,
    0x44080088080100ULL,
    0x922820441001400ULL,
    0x4a80080242101ULL,
    0x441004100010ULL,
    0x802828410120000ULL,
    0x800428401210209ULL,
    0x2050020880800ULL,
    0x9011004618200c0ULL,
    0x154b45012020818ULL,
    0x20022208210112ULL,
    0x8002900404808200ULL,
    0x48602c0048080800ULL,
    0x8080108208018450ULL,
    0xc130060044040408ULL,
    0x4008000202104400ULL,
    0x5800200041104100ULL,
    0x4200400510020200ULL,
    0x11b042048020080ULL,
    0x4f00401002200ULL,
};

unsigned int getrand32() {
    unsigned int x = RANDOM_STATE;

    //XOR shift algorithm
    x ^= (x << 13);
    x ^= (x >> 17);
    x ^= (x << 5);
    RANDOM_STATE = x;
    return x;
}

uint64 getrand64() {
    uint64 a, b, c, d;
    a = (uint64)(getrand32()) & 0xFFFF;
    b = (uint64)(getrand32()) & 0xFFFF;
    c = (uint64)(getrand32()) & 0xFFFF;
    d = (uint64)(getrand32()) & 0xFFFF;

    return a | (b << 16) | (c << 32) | (d << 48);
}

uint64 randomuint64fewbits() {
    return getrand64() & getrand64() & getrand64();
}

int transform(uint64 b, uint64 magic, int bits) {
#if defined(USE_32_BIT_MULTIPLICATIONS)
    return (unsigned)((int)b*(int)magic ^ (int)(b>>32)*(int)(magic>>32)) >> (32-bits);
#else
  return (int)((b * magic) >> (64 - bits));
#endif
}

uint64 findMagic(int square, int relevant_bits, int bishop)
{
    uint64 occupancies[4096];
    uint64 attacks[4096];
    uint64 used_attacks[4096];
    uint64 attack_mask = bishop ? bmask(square) : rmask(square);
    int occupancy_indicies = 1 << relevant_bits;
    
    for (int index = 0; index < occupancy_indicies; index++)
    {
        occupancies[index] = setOccupancy(index, relevant_bits, attack_mask);
        attacks[index] = bishop ? batt(square, occupancies[index]) : ratt(square, occupancies[index]);
    }

    // test magic numbers loop
    for (int random_count = 0; random_count < 100000000; random_count++) {
        uint64 magic_number = randomuint64fewbits();
        if (count_1s((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        int index, fail;

        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++) {
        int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));
        if (used_attacks[magic_index] == 0ULL) used_attacks[magic_index] = attacks[index];
        else if (used_attacks[magic_index] != attacks[index]) fail = 1;
        }

        if (!fail) return magic_number;
    }
}

void initMagicNumbers() {
    printf("Rook Magics:\n");
    for(int i = 0; i < 64; i++){
        printf("0x%llxULL, \n", findMagic(i, relevantRookBits[i], rook));
    }
    printf("\n\n\nBishop Magics:\n");
    for(int i = 0; i < 64; i++){
        printf("0x%llxULL, \n", findMagic(i, relevantBishopBits[i], bishop));
    }
}

void initRandomizingRoutines() {
    RANDOM_STATE = 1804289383; // Reset the random state
    //initMagicNumbers(); // used this code to generate the magic numbers, but now we can declare them as constants instead
}

