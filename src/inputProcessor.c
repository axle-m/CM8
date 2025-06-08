#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"

int squareToPos(char *square) {\
    int file = square[0] - 'a';
    int rank = 8 - (square[1] - '0');
    return rank * 8 + file;
}

void parseFen(char *fen){
    //reset everything
    memset(bitboards, 0ULL, sizeof(bitboards));
    memset(occupancies, 0ULL, sizeof(occupancies));
    side = white;
    enpassant = no_sq;
    castle = 0;

    //piece placement
    int rank = 0, file = 0;
    while(*fen != ' ') {
        char c = *fen;
        *fen++;
        if(c == '/') {
            rank++;
            file = 0;
        } else if(c >= '1' && c <= '8') {
            file += c - '0';
        } else {
            int piece;
            switch(c) {
                case 'P': piece = P; break;
                case 'N': piece = N; break;
                case 'B': piece = B; break;
                case 'R': piece = R; break;
                case 'Q': piece = Q; break;
                case 'K': piece = K; break;
                case 'p': piece = p; break;
                case 'n': piece = n; break;
                case 'b': piece = b; break;
                case 'r': piece = r; break;
                case 'q': piece = q; break;
                case 'k': piece = k; break;
                default: continue;
            }
            int sq = rank * 8 + file;
            SET_BIT(bitboards[piece], sq);
            file++;
        }
    }
    *fen++;

    //init occupancy bitboards
    for(int piece = P; piece <= K; piece++) occupancies[white] |= bitboards[piece];
    for(int piece = p; piece <= k; piece++) occupancies[black] |= bitboards[piece];
    occupancies[both] = occupancies[white] | occupancies[black];

    //side to move
    side = (*fen == 'w') ? white : black;
    *fen++;
    *fen++;

    //castling rights
    while(*fen != ' ') {
        switch(*fen) {
            case 'K': castle |= WK; break;
            case 'Q': castle |= WQ; break;
            case 'k': castle |= BK; break;
            case 'q': castle |= BQ; break;
            case '-': break;
        }
        *fen++;
    }
    *fen++;

    //en passant
    enpassant = (*fen == '-') ? no_sq : squareToPos(fen);
    while(*fen != ' ' && *fen != '\0') *fen++;
    *fen++;

//     //halfmove clock
//     while(*fen != ' ') *fen++;
//     *fen++;

//     //fullmove number
//     while(*fen != ' ' && *fen != '\0') *fen++;
}