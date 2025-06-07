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

#include "bit.h"
#include "attackTables.h"
#include "randomizingRoutines.h"

unsigned int RANDOM_STATE = 1804289383;

const U64 ROOK_MAGICS[64] = {
    0x4010a02202800040ULL, 
    0x400c202000200010ULL, 
    0x2410800004010e4ULL, 
    0xc08043000100102ULL, 
    0x888400800800204ULL, 
    0x102004000400104ULL, 
    0x110a0c020004c2ULL, 
    0x248000800049ULL, 
    0x2204440040808080ULL, 
    0x44900884004028ULL, 
    0x41a00500010031ULL,
    0x81000a484088008ULL, 
    0x880080302208204ULL, 
    0x80240888008202ULL, 
    0x101180c10020042ULL,
    0x8002c002088081ULL, 
    0xaa5880001004040ULL, 
    0x10c28a088100a101ULL, 
    0x4030044000080020ULL,
    0x204a010001061010ULL, 
    0xc00802a00004808ULL, 
    0x402050002008082ULL, 
    0x8001020000008083ULL, 
    0x621005a00208101ULL, 
    0x208b002880800441ULL, 
    0x15000a100002041ULL, 
    0x8012004400018222ULL,
    0x602c100000406101ULL, 
    0x2b002404041022ULL, 
    0x4004ca2020005042ULL, 
    0x6a04014200c10005ULL,
    0x111904150100cc2ULL, 
    0x80008240006a40ULL, 
    0x204000c014101020ULL,
    0x2404020444408320ULL, 
    0xd01002081080110ULL, 
    0x2040040002180542ULL,
    0x80020800208014ULL, 
    0x100840302810006ULL, 
    0x300808004030201ULL, 
    0x8000100040214028ULL, 
    0xab4410000a400084ULL, 
    0x10100c11208204ULL, 
    0x308100024581018ULL, 
    0x809001040000508ULL, 
    0x45a00442032820aULL, 
    0x2014040802010866ULL, 
    0x2050808040450441ULL, 
    0x800080101aa640ULL, 
    0x400840830406002ULL, 
    0x1084002008080030ULL, 
    0x880080460044108ULL, 
    0x8008282008024ULL, 
    0x5528020200001402ULL, 
    0x81820008240846ULL, 
    0x4000808000820241ULL, 
    0x582482200001102ULL, 
    0x400ca500001025ULL, 
    0x820018940143041ULL, 
    0x1000050105210bULL, 
    0x4102308410801ULL, 
    0x80104020204552aULL, 
    0x100088420202018eULL, 
    0x9280228720000049ULL
};
const U64 BISHOP_MAGICS[64] = {
    0x10c348112161014ULL,
    0x11442908112002a4ULL,
    0x9c840000091902ULL,
    0x2802201201441042ULL,
    0x924003091040ULL,
    0x4044120010a0c818ULL, 
    0x804040005048502ULL, 
    0x2404246000003406ULL,
    0x409086140021a10ULL,
    0x4102065240141204ULL,
    0x3400510120020465ULL, 
    0x5084111408002404ULL,
    0x4040280402014a1ULL,
    0x2422001410008301ULL,
    0x2482280422009404ULL, 
    0x901144500000189ULL, 
    0xa108018800920445ULL, 
    0xb404228000160860ULL,
    0xc100620002112498ULL, 
    0x410920008c088405ULL, 
    0x2501210020222481ULL,
    0x210086001801000aULL,
    0x482390400440082ULL, 
    0x40501000140b00bULL, 
    0x4080a0089616270ULL,
    0x684040000101440ULL,
    0x1400a40000004809ULL,
    0x2009010400008180ULL, 
    0x811040070881080ULL, 
    0x840500800814202ULL, 
    0x604c40000012402ULL,
    0x80a85004028432ULL,
    0x2050842006080290ULL,
    0x12a300400031410ULL,
    0x182000000a809ULL, 
    0x1200a00200040b2ULL,
    0x4150410000490224ULL, 
    0x284b0200020802ULL, 
    0x1029010004490802ULL,
    0x2020410131909212ULL,
    0x48010a2300020110ULL, 
    0x2814aa0406008404ULL,
    0x2222010002020104ULL, 
    0x4090040009042914ULL,
    0x84050211101105c5ULL,
    0x20024000400108ULL, 
    0x8024011002160cULL,
    0xa5032200440144ULL,
    0x44054920009008aULL, 
    0x20200140301048aULL,
    0x124820900088144ULL, 
    0x1090920006024012ULL, 
    0x2212030000848413ULL,
    0x806030000094424ULL,
    0x8c004044210802ULL,
    0x1102104401100301ULL, 
    0x8801928000002415ULL,
    0x882060002648151ULL,
    0x210920000a41082ULL, 
    0x8a420622a4840400ULL,
    0x100a12020002c010ULL, 
    0x810010c21000404ULL,
    0x208830004045020ULL, 
    0x404428002022002ULL, 
};

const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
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

U64 getrand64() {
    U64 a, b, c, d;
    a = (U64)(getrand32()) & 0xFFFF;
    b = (U64)(getrand32()) & 0xFFFF;
    c = (U64)(getrand32()) & 0xFFFF;
    d = (U64)(getrand32()) & 0xFFFF;

    return a | (b << 16) | (c << 32) | (d << 48);
}

U64 randomU64fewbits() {
  return getrand64() & getrand64() & getrand64();
}

int pop1st(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

U64 indexToU64(int index, int bits, U64 m) {
    int i, j;
    U64 result = 0ULL;
    for(i = 0; i < bits; i++) {
        j = pop1st(&m);
        if(index & (1 << i)) result |= (1ULL << j);
    }
    return result;
}

int transform(U64 b, U64 magic, int bits) {
#if defined(USE_32_BIT_MULTIPLICATIONS)
    return (unsigned)((int)b*(int)magic ^ (int)(b>>32)*(int)(magic>>32)) >> (32-bits);
#else
  return (int)((b * magic) >> (64 - bits));
#endif
}

U64 findMagic(int square, int relevantBits, int bishop) {
    U64 mask, b[4096], a[4096], used[4096], magic;
    int i, j, k, n, fail;

    mask = bishop? maskBishopAttacks(square) : maskRookAttacks(square);
    n = countBits(mask);

    for(i = 0; i < (1 << n); i++) {
        b[i] = indexToU64(i, n, mask);
        a[i] = bishop? genBishopAttacks(square, b[i]) : genRookAttacks(square, b[i]);
    }
    for(k = 0; k < 100000000; k++) {
        magic = randomU64fewbits();
        if(countBits((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
        for(i = 0; i < 4096; i++) used[i] = 0ULL;
        for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
            j = transform(b[i], magic, relevantBits);
            if(used[j] == 0ULL) used[j] = a[i];
            else if(used[j] != a[i]) fail = 1;
        }
        if(!fail) return magic;
    }
    printf("***Failed***\n");
    return 0ULL;
}

void initMagicNumbers() {
    printf("Rook Magics:\n");
    for(int i = 0; i < 64; i++){
        printf("0x%llxULL, \n", findMagic(i, relevantRookBitCounts[i], rook));
    }
    printf("\n\n\nBishop Magics:\n");
    for(int i = 0; i < 64; i++){
        printf("0x%llxULL, \n", findMagic(i, relevantBishopBitCounts[i], bishop));
    }
}

void initRandomizingRoutines() {
    RANDOM_STATE = 1804289383; // Reset the random state
    //initMagicNumbers(); // used this code to generate the magic numbers, but now we can declare them as constants instead
}

