#include <stdio.h>
#include <stdlib.h>


#ifndef eval
#define eval
#include "moveGenerator.h"
#include "bit.h"

int materialScores[12];
const int pawn_pcsq[64];
const int knight_pcsq[64];
const int rook_pcsq[64];
const int king_pcsq[64];
const int bishop_pcsq[64];
const int king_endgame_pcsq[64];
const int mirrorScore[128];
const int mvv_lva[12][12];

int ply;

// [id][ply]
int killerMoves[2][64];

// [piece][pos]
int historyMoves[12][64]; // history table for each piece type and square

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
                case K: 
                    if(pieces < 15) {
                        score += king_endgame_pcsq[pos]; // endgame king positional score
                    } else {
                        score += king_pcsq[pos]; // middlegame king positional score
                    }
                    break;

                case p: score -= pawn_pcsq[mirrorScore[pos]]; break;
                case n: score -= knight_pcsq[mirrorScore[pos]]; break;
                case b: score -= bishop_pcsq[mirrorScore[pos]]; break;
                case r: score -= rook_pcsq[mirrorScore[pos]]; break;
                case k: 
                    if(pieces < 15) {
                        score -= king_endgame_pcsq[mirrorScore[pos]]; // endgame king positional score
                    } else {
                        score -= king_pcsq[mirrorScore[pos]]; // middlegame king positional score
                    }
                    break;

                default: break;
            }
        }
    }

    return score * (side == white ? 1 : -1);
}

int bestMove;

uint64 nodes;

static inline int scoreMove(int move){
    if(GET_MOVE_CAPTURE(move)) {
        int piece = P;
        int start, end;
        if(side == white) { start = p; end = k; }
        else { start = P; end = K; }

        for(int pce = start; pce <= end; pce++) {
            if(GET_BIT(bitboards[pce], GET_MOVE_TARGET(move))) {
                piece = pce;
                break;
            }
        }

        return mvv_lva[GET_MOVE_PIECE(move)][piece] + 10000;
    } else {
        if(killerMoves[0][ply] == move) return 9000;
        if(killerMoves[1][ply] == move) return 8000;
        else return historyMoves[GET_MOVE_PIECE(move)][GET_MOVE_TARGET(move)];
    }
    return 0;
}

static inline void merge(int *moves, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    if (n1 > 256 || n2 > 256) {
        printf("merge buffer overflow: n1=%d n2=%d\n", n1, n2);
        exit(1);
    }

    int L[256], R[256]; // assuming moveList never exceeds 256 moves

    for (int i = 0; i < n1; i++)
        L[i] = moves[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = moves[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (scoreMove(L[i]) >= scoreMove(R[j])) { // descending order
            moves[k++] = L[i++];
        } else {
            moves[k++] = R[j++];
        }
    }
    while (i < n1)
        moves[k++] = L[i++];
    while (j < n2)
        moves[k++] = R[j++];
}

static inline void mergeSortMoves(int *moves, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortMoves(moves, left, mid);
        mergeSortMoves(moves, mid + 1, right);
        merge(moves, left, mid, right);
    }
}

static inline int compareMoves(const void *a, const void *b) {
    int scoreA = scoreMove(*(const int *)a);
    int scoreB = scoreMove(*(const int *)b);
    return (scoreB - scoreA); // descending order
}

static inline void sort(moveList *list) {
    if (list->count > 1)
        qsort(list->moves, list->count, sizeof(int), compareMoves);
    // if (list->count > 1)
    //     mergeSortMoves(list->moves, 0, list->count - 1);
}

static inline int quiescence(int alpha, int beta) {
    nodes++;
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
    sort(captures);

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
    if(depth > 20) {
        return (alpha > beta) ? alpha : beta; // fail-soft
    }

    int isKingInCheck = isSquareAttacked((side == white ? getLSBIndex(bitboards[k]) : getLSBIndex(bitboards[K])), side ^ 1);
    //if(isKingInCheck & 1) depth++; // increase depth if king is in check

    legalMovesCount = 0;

    int bestSoFar;
    int oldAlpha = alpha;

    moveList moves[1];
    generateMoves(moves);
    sort(moves);
    
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
            killerMoves[1][ply] = killerMoves[0][ply]; // store the killer move
            killerMoves[0][ply] = move; // update the second killer move

            return beta; // fail high
        }
        
        if(score > alpha) {
            historyMoves[GET_MOVE_PIECE(move)][GET_MOVE_TARGET(move)] += depth; // update history table

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