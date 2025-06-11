#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"

void oneVsOne(){ 
    // parseFen(start_position);
    // char player = 'W';
    // char *move = (char *)malloc(10 * sizeof(char));

    // while(1) {
    //     printf("Player %c's turn. Enter your move: ", player);
    //     fgets(move, 10, stdin);
    //     move[strcspn(move, "\n")] = 0;  // Remove newline character

    //     if(strcmp(move, "exit") == 0) {
    //         printf("Exiting game.\n");
    //         free(move);
    //         return;
    //     }

    //     int promotionFlag = 0;

    //     if((move[0] == 'P'|| move[0] == 'p') && (squareToPos(move + 3) < h8 || squareToPos(move + 3) > a1)) {
    //         promotionFlag = 1;
    //     }

    //     if(!makePlayerMove(move, promotionFlag)) {
    //         printf("Invalid move. Try again.\n");
    //     }

    //     player = (player == 'W') ? 'B' : 'W'; // Switch player
    //     printBoard();
    // }
}

int materialScores[12] = {
    [P] = 100, [N] = 300, [B] = 300, [R] = 500, [Q] = 900, [K] = 10000,
    [p] = -100, [n] = -300, [b] = -300, [r] = -500, [q] = -900, [k] = -10000
};

// pawn positional score
int pawn_pcsq[64] = {
	  20, 20,  20,  20,  20,  20,  20,  20,
	  5,  10,  15,  20,  20,  15,  10,   5,
	  4,   8,  12,  16,  16,  12,   8,   4,
	  3,   6,   9,  12,  12,   9,   6,   3,
	  2,   4,   6,   8,   8,   6,   4,   2,
	  1,   2,   3, -10, -10,   3,   2,   1,
	  0,   0,   0, -40, -40,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0
};

int knight_pcsq[64] = {
	-10, -10, -10, -10, -10, -10, -10, -10,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10,   0,   5,   5,   5,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,   5,   5,   5,   0, -10,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10, -30, -10, -10, -10, -10, -30, -10
};

int bishop_pcsq[64] = {
	-10, -10, -10, -10, -10, -10, -10, -10,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10,   0,   5,   5,   5,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,  10,  10,   5,   0, -10,
	-10,   0,   5,   5,   5,   5,   0, -10,
	-10,   0,   0,   0,   0,   0,   0, -10,
	-10, -10, -20, -10, -10, -20, -10, -10
};

int king_pcsq[64] = {
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-20, -20, -20, -20, -20, -20, -20, -20,
	  0,  20,  40, -20,   0, -20,  40,  20
};

int king_endgame_pcsq[64] = {
	  0,  10,  20,  30,  30,  20,  10,   0,
	 10,  20,  30,  40,  40,  30,  20,  10,
	 20,  30,  40,  50,  50,  40,  30,  20,
	 30,  40,  50,  60,  60,  50,  40,  30,
	 30,  40,  50,  60,  60,  50,  40,  30,
	 20,  30,  40,  50,  50,  40,  30,  20,
	 10,  20,  30,  40,  40,  30,  20,  10,
	  0,  10,  20,  30,  30,  20,  10,   0
};

// mirror positional score tables for opposite side
const int mirrorScore[128] =
{
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

void init() {
    nodes = 0;
    bestMove = 0;
    initAttackTables();
    initRandomizingRoutines();
}

void cleanup(){
    // for(int i = 0; i < 64; i++) {
    //     free(mBishopTable[i]);
    //     free(mRookTable[i]);
    // }
    // printf("Cleanup done.\n");
}

uint64 unix_time_ms() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64 t = ((uint64)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    // FILETIME is in 100-nanosecond intervals since Jan 1, 1601
    // Convert to milliseconds since Unix epoch (Jan 1, 1970)
    return (t - 116444736000000000ULL) / 10000ULL;
}
