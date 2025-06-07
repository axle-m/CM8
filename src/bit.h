typedef unsigned long long uint64;

#ifndef MACROS
#define MACROS
#define SET_BIT(bb, pos) ((bb) |= (1ULL << (pos)))
#define GET_BIT(bb, pos) (bb & (1ULL << (pos)) ? 1 : 0)
#define CLEAR_BIT(bb, pos)  ((bb) &= ~(1ULL << (pos)))
#define SWAP_BITS(bb, pos1, pos2) \
    do { \
        uint64 temp = (bb); \
        int bit1 = GET_BIT(temp, pos1); \
        int bit2 = GET_BIT(temp, pos2); \
        temp = (bit1 ? SET_BIT(temp, pos2) : CLEAR_BIT(temp, pos2)); \
        temp = (bit2 ? SET_BIT(temp, pos1) : CLEAR_BIT(temp, pos1)); \
        (bb) = temp; \
    } while (0)

enum { rook, bishop }; //replace rook with 0, bishop with 1

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_sq
};

enum { white, black, both };

enum { WK = 1, WQ = 2, BK = 4, BQ = 8 };
    // 0001 : white kingside
    // 0010 : white queenside
    // 0100 : black kingside
    // 1000 : black queenside

enum { P, N, B, R, Q, K, p, n, b, r, q, k, EMPTY };

uint64 bitboards[12];
uint64 occupancies[3];
int side;
int enpassant;
int castle;
const char *squareToCoords[64];
char asciiPieces[12];
int char_pieces[12];

#endif

void printBitboard(uint64 bitboard);
int countBits(uint64 bitboard);
int getLSBIndex(uint64 bitboard);
int pop_1st_bit(uint64 *bb);
uint64 index_to_uint64(int index, int bits, uint64 m);
int count_1s(uint64 bb);