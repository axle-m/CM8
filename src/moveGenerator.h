#include "bit.h"
#include "attackTables.h"

// returns 1 if the given square is attacked by any piece on the given side
static inline int isSquareAttacked(int sq, int side){
    // pawns
    if((side == white)  && (pawnAttacks[black][sq] & bitboards[P])) return 1;
    if((side == black)  && (pawnAttacks[white][sq] & bitboards[p])) return 1;
    // knights
    if(knightAttacks[sq] & (side == white ? bitboards[N] : bitboards[n])) return 1;
    // kings
    if(kingAttacks[sq] & (side == white ? bitboards[K] : bitboards[k])) return 1;
    // bishops and queens
    if(bishopAttacks(occupancies[both], sq) & (side == white ? (bitboards[B] | bitboards[Q]) : (bitboards[b] | bitboards[q]))) return 1;
    // rooks and queens
    if(rookAttacks(occupancies[both], sq) & (side == white ? (bitboards[R] | bitboards[Q]) : (bitboards[r] | bitboards[q]))) return 1;
    return 0;
}

void printAttackedSquares(int side); // prints all the squares attacked by the given side
void generateMoves();          // generates all pseudo-legal moves for the current position