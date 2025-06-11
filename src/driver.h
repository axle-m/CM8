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

#define LIMIT 5000 //time limit in ms
uint64 START_TIME; // start time in ms

void oneVsOne();
void init();
void cleanup();
uint64 unix_time_ms();

int materialScores[12];
const int pawn_pcsq[64];
const int knight_pcsq[64];
const int rook_pcsq[64];
const int king_pcsq[64];
const int bishop_pcsq[64];
const int king_endgame_pcsq[64];
const int mirrorScore[128];

static inline int evaluate() {
    int score = 0;
    uint64 bb;
    int piece, pos;
    int pieces = count_1s(occupancies[both]);

    for(int pce = P; pce <= k; pce++) {
        bb = bitboards[pce];
        while(bb) {
            pos = pop_1st_bit(&bb);
            score += materialScores[pce];
            switch(pce) {
                case P: score += pawn_pcsq[pos]; break;
                case N: score += knight_pcsq[pos]; break;
                case B: score += bishop_pcsq[pos]; break;
                case R: score += rook_pcsq[pos]; break;
                case K: score += king_pcsq[pos]; break;

                case p: score -= pawn_pcsq[mirrorScore[pos]]; break;
                case n: score -= knight_pcsq[mirrorScore[pos]]; break;
                case b: score -= bishop_pcsq[mirrorScore[pos]]; break;
                case r: score -= rook_pcsq[mirrorScore[pos]]; break;
                case k: score -= king_pcsq[mirrorScore[pos]]; break;
                
                default: break;
            }
        }
    }

    return score * (side == white ? 1 : -1);
}

int bestMove;

uint64 nodes;

static inline int quiescence(int alpha, int beta) {
    int standPat = evaluate();
    if(standPat >= beta) return beta;
    if(standPat > alpha) alpha = standPat;
    // if(unix_time_ms() - START_TIME > LIMIT) {
    //     return alpha; // time limit exceeded
    // }
    //if(depth == 0) return alpha; // quiescence search depth limit reached

    // Generate all possible captures
    moveList captures[1];
    generateMoves(captures);

    for(int i = 0; i < captures->count; i++) {
        COPY_BOARD;
        ply++;

        int move = captures->moves[i];

        // make the move
        if(!makeMove(move, capture)){
            ply--;
            continue;
        }

        // negamax
        int score = -quiescence(-beta, -alpha);

        // take back the move
        TAKE_BACK;
        ply--;

        if(score >= beta) {
            return beta; // fail high
        }

        if(score > alpha) {
            alpha = score;
        }
    }

    return alpha;
}

static inline int negamax(int alpha, int beta, int depth){
    if (depth == 0) {
        nodes++;
        //return evaluate(); // return evaluation at leaf nodes
        return quiescence(alpha, beta); // quiescence search at leaf nodes
    }

    int isKingInCheck = isSquareAttacked((side == white ? getLSBIndex(bitboards[k]) : getLSBIndex(bitboards[K])), side ^ 1);

    legalMovesCount = 0;

    int bestSoFar;
    int oldAlpha = alpha;

    moveList moves[1];
    generateMoves(moves);
    
    for(int i = 0; i < moves->count; i++) {
        COPY_BOARD;
        ply++;

        int move = moves->moves[i];

        // make the move
        if(!makeMove(move, all)) {
            ply--;
            continue;
        }

        // negamax
        int score = -negamax(-beta, -alpha, depth - 1);

        // take back the move
        TAKE_BACK;
        ply--;

        legalMovesCount++;

        if(score >= beta) {
            return beta; // fail high
        }
        
        if(score > alpha) {
            alpha = score;
            if(ply == 0) {
                bestSoFar = move; // store the best move at root level
            }
        }
    }

    if(legalMovesCount == 0) {
        if(isKingInCheck) {
            return -49000 + ply; // checkmate
        } else {
            return 0; // stalemate
        }
    }

    if(oldAlpha != alpha) {
        bestMove = bestSoFar; // update the best move if alpha has changed
    }

    //fails low
    return alpha;
}

static inline int getBestMove(int depth) {
    int score = negamax(-50000, 50000, depth);
    printf("Best: ");
    PRINT_MOVE(bestMove);
    return bestMove;
}

#endif