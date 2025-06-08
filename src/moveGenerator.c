#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moveGenerator.h"

void printAttackedSquares(int side) {
    printf("Squares attacked by %s:\n", side == white ? "White" : "Black");
    uint64 attackedSquares = 0ULL;

    // Iterate through all squares
    for (int sq = 0; sq < 64; sq++) {
        if (isSquareAttacked(sq, side)) {
            SET_BIT(attackedSquares, sq);
        }
    }

    printBitboard(attackedSquares);
}

void generateMoves() {
    int from, to;
    uint64 bb, attacks;
    
    for(int piece = P; piece <= k; piece++){
        bb = bitboards[piece];

        //generate white pawns & castle
        if(side == white) {
                if(piece == P) {
                while(bb){
                    from = getLSBIndex(bb);
                    to = from - 8;
                    //quiet pawn moves
                    if((to >= a8) && !GET_BIT(occupancies[both], to)){
                        //promotion
                        if(from >= a7 && from <= h7){
                            //generate all 4 promotion moves
                            printf("pawn promotion %s%s=Q\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn promotion %s%s=R\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn promotion %s%s=B\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn promotion %s%s=N\n", squareToCoords[from], squareToCoords[to]);
                        }
                        else {
                        // single push
                            printf("pawn single push %s%s\n", squareToCoords[from], squareToCoords[to]);
                        // double push
                            if(from >= a2 && from <= h2){
                                to = from - 16;
                                if(!GET_BIT(occupancies[both], to)){
                                    printf("pawn double push %s%s\n", squareToCoords[from], squareToCoords[to]);
                                }
                            }
                        }
                    }

                    //captures
                    attacks = pawnAttacks[white][from] & occupancies[black];
                    while(attacks) {
                        to = getLSBIndex(attacks);
                        if(from >= a7 && from <= h7){
                            //generate all 4 promotion moves
                            printf("pawn capture promotion %s%s=Q\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=R\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=B\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=N\n", squareToCoords[from], squareToCoords[to]);
                        }
                        else{
                            printf("pawn capture %s%s\n", squareToCoords[from], squareToCoords[to]);
                        }
                        CLEAR_BIT(attacks, to);
                    }

                    if(enpassant != no_sq) {
                        uint64 enpassantAttacks = pawnAttacks[white][from] & (1ULL << enpassant);
                        if(enpassantAttacks) {
                            printf("en passant %s%s\n", squareToCoords[from], squareToCoords[enpassant]);
                        }
                    }

                    //pop ls1b from bb
                    CLEAR_BIT(bb, from);
                }
            }
            //castling
            else if(piece == K) {
                if(castle & WK) {
                    //white kingside castle
                    //if both kingside squares are empty and do not pass through check
                    if(!GET_BIT(occupancies[both], f1) && !GET_BIT(occupancies[both], g1)) {
                        if(!isSquareAttacked(e1, black) && !isSquareAttacked(f1, black)){
                            printf("white kingside castle e1g1\n");
                        }
                    }
                }
                if(castle & WQ) {
                    //white queenside castle
                    //if all 3 queenside squares are empty
                    if(!GET_BIT(occupancies[both], d1) && !GET_BIT(occupancies[both], c1) && !GET_BIT(occupancies[both], b1)) {
                        //if e1 and d1 do not pass through check
                        if(!isSquareAttacked(e1, black) && !isSquareAttacked(d1, black)){
                            printf("white queenside castle e1c1\n");
                        }
                    }
                }
            }
        }
        //generate black pawns & castle
        else {
            if(piece == p) {
                while(bb){
                    from = getLSBIndex(bb);
                    to = from + 8;
                    //quiet pawn moves
                    if((to <= h1) && !GET_BIT(occupancies[both], to)){
                        //promotion
                        if(from >= a2 && from <= h2){
                            //generate all 4 promotion moves
                            printf("black promotion %s%s=Q\n", squareToCoords[from], squareToCoords[to]);
                            printf("black promotion %s%s=R\n", squareToCoords[from], squareToCoords[to]);
                            printf("black promotion %s%s=B\n", squareToCoords[from], squareToCoords[to]);
                            printf("black promotion %s%s=N\n", squareToCoords[from], squareToCoords[to]);
                        }
                        else {
                        // single push
                            printf("black single push %s%s\n", squareToCoords[from], squareToCoords[to]);
                        // double push
                            if(from >= a7 && from <= h7){
                                to = from + 16;
                                if(!GET_BIT(occupancies[both], to)){
                                    printf("black double push %s%s\n", squareToCoords[from], squareToCoords[to]);
                                }
                            }
                        }
                    }

                    //captures
                    attacks = pawnAttacks[black][from] & occupancies[white];
                    while(attacks) {
                        to = getLSBIndex(attacks);
                        if(from >= a2 && from <= h2){
                            //generate all 4 promotion moves
                            printf("pawn capture promotion %s%s=Q\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=R\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=B\n", squareToCoords[from], squareToCoords[to]);
                            printf("pawn capture promotion %s%s=N\n", squareToCoords[from], squareToCoords[to]);
                        }
                        else{
                            printf("pawn capture %s%s\n", squareToCoords[from], squareToCoords[to]);
                        }
                        CLEAR_BIT(attacks, to);
                    }

                    if(enpassant != no_sq) {
                        uint64 enpassantAttacks = pawnAttacks[black][from] & (1ULL << enpassant);
                        if(enpassantAttacks) {
                            printf("en passant %s%s\n", squareToCoords[from], squareToCoords[enpassant]);
                        }
                    }

                    //pop ls1b from bb
                    CLEAR_BIT(bb, from);
                }
            }
            else if(piece == k) {
                if(castle & BK) {
                    //black kingside castle
                    //if both kingside squares are empty and do not pass through check
                    if(!GET_BIT(occupancies[both], f8) && !GET_BIT(occupancies[both], g8)) {
                        if(!isSquareAttacked(e8, white) && !isSquareAttacked(f8, white)){
                            printf("black kingside castle e8g8\n");
                        }
                    }
                }
                if(castle & BQ) {
                    //black queenside castle
                    //if all 3 queenside squares are empty
                    if(!GET_BIT(occupancies[both], d8) && !GET_BIT(occupancies[both], c8) && !GET_BIT(occupancies[both], b8)) {
                        //if e8 and d8 do not pass through check
                        if(!isSquareAttacked(e8, white) && !isSquareAttacked(d8, white)){
                            printf("black queenside castle e8c8\n");
                        }
                    }
                }
            }
        }    

        //gen knight moves

        //gen bishop moves

        //gen rook moves

        //gen queen moves

        //gen king moves
    }
}