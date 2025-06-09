#include "bit.h"
#include "attackTables.h"
#include "inputProcessor.h"

#ifndef MOVE_MACROS
#define MOVE_MACROS
#define ENCODE_MOVE(from, to, piece, promoted, capture, doublePush, enPassant, castle) \
    (from) | (to << 6) | (piece << 12) | (promoted << 16) | (capture << 20) | (doublePush << 21) | (enPassant << 22) | (castle << 23)
#define GET_MOVE_SOURCE(move) ((move) & 0x3f)
#define GET_MOVE_TARGET(move) (((move) & 0xfc0) >> 6)
#define GET_MOVE_PIECE(move) (((move) & 0xf000) >> 12)
#define GET_PROMOTED_PIECE(move) (((move) & 0xf0000) >> 16)
#define GET_MOVE_CAPTURE(move) (((move) & 0x100000) /* >> 20*/)         // shifts not needed because we just need a boolean (>0 for true)
#define GET_MOVE_DOUBLE_PUSH(move) (((move) & 0x200000) /* >> 21*/)
#define GET_MOVE_EN_PASSANT(move) (((move) & 0x400000) /* >> 22*/)
#define GET_MOVE_CASTLE(move) (((move) & 0x800000) /* >> 23*/)
#define PRINT_MOVE_COMPLETE(move) printf("%c%s%s%c %s %s %s %s\n", \
    asciiPieces[GET_MOVE_PIECE(move)], \
    squareToCoords[GET_MOVE_SOURCE(move)], \
    squareToCoords[GET_MOVE_TARGET(move)], \
    promotedPieces[GET_PROMOTED_PIECE(move)], \
    GET_MOVE_CAPTURE(move) ? "captures" : "", \
    GET_MOVE_DOUBLE_PUSH(move) ? "double push" : "", \
    GET_MOVE_EN_PASSANT(move) ? "en passant" : "", \
    GET_MOVE_CASTLE(move) ? "castle" : "")
#define PRINT_MOVE(move) printf("%c%s%s", \
    asciiPieces[GET_MOVE_PIECE(move)], \
    squareToCoords[GET_MOVE_SOURCE(move)], \
    squareToCoords[GET_MOVE_TARGET(move)]); \
    GET_PROMOTED_PIECE(move) ? printf("=%c\n", promotedPieces[GET_PROMOTED_PIECE(move)]) : printf("\n")
#endif

#ifndef COPYPASTE
#define COPYPASTE

#define COPY_BOARD \
    uint64 bb_cpy[12], occ_cpy[3]; \
    int side_cpy, ep_cpy, castle_cpy; \
    memcpy(bb_cpy, bitboards, 96); \
    memcpy(occ_cpy, occupancies, 24); \
    side_cpy = side; \
    ep_cpy = enpassant; \
    castle_cpy = castle;
    //ONLY TAKE BACK IF YOU HAVE COPIED A BOARD PREVIOUSLY
#define TAKE_BACK \
    memcpy(bitboards, bb_cpy, 96); \
    memcpy(occupancies, occ_cpy, 24); \
    side = side_cpy; \
    enpassant = ep_cpy; \
    castle = castle_cpy;
#endif

//move flags
enum { all, capture };

const int castleUpdate[64]; // updates castling rights based on the move made

char promotedPieces[11];

typedef struct moveList {
    int moves[256];
    int count;
} moveList;

static inline void initMoveList(moveList *list) {
    list->count = 0;
}

static inline void addMove(moveList *list, int move) {
    list->moves[list->count] = move;
    list->count++;
}

static inline void printMoveList(moveList *list) {
    if(list->count == 0) {
        printf("No moves generated.\n");
        return;
    }
    for(int i = 0; i < list->count; i++) {
        PRINT_MOVE_COMPLETE(list->moves[i]);
    }
    printf("Total moves: %d\n", list->count);
}

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

static inline void generateMoves(moveList *list) { // generates all pseudo-legal moves for the current position
    initMoveList(list);

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
                            addMove(list, ENCODE_MOVE(from, to, P, Q, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, R, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, B, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, N, 0, 0, 0, 0));
                        }
                        else {
                        // single push
                            addMove(list, ENCODE_MOVE(from, to, P, 0, 0, 0, 0, 0));
                        // double push
                            if(from >= a2 && from <= h2){
                                to = from - 16;
                                if(!GET_BIT(occupancies[both], to)){
                                    addMove(list, ENCODE_MOVE(from, to, P, 0, 0, 1, 0, 0));
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

                            addMove(list, ENCODE_MOVE(from, to, P, Q, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, R, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, B, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, P, N, 1, 0, 0, 0));
                        }
                        else{
                            addMove(list, ENCODE_MOVE(from, to, P, 0, 1, 0, 0, 0));
                        }
                        CLEAR_BIT(attacks, to);
                    }

                    if(enpassant != no_sq) {
                        uint64 enpassantAttacks = pawnAttacks[white][from] & (1ULL << enpassant);
                        if(enpassantAttacks) {
                            addMove(list, ENCODE_MOVE(from, enpassant, P, 0, 1, 0, 1, 0));
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
                            addMove(list, ENCODE_MOVE(e1, g1, K, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if(castle & WQ) {
                    //white queenside castle
                    //if all 3 queenside squares are empty
                    if(!GET_BIT(occupancies[both], d1) && !GET_BIT(occupancies[both], c1) && !GET_BIT(occupancies[both], b1)) {
                        //if e1 and d1 do not pass through check
                        if(!isSquareAttacked(e1, black) && !isSquareAttacked(d1, black)){
                            addMove(list, ENCODE_MOVE(e1, c1, K, 0, 0, 0, 0, 1));
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
                            addMove(list, ENCODE_MOVE(from, to, p, q, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, r, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, b, 0, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, n, 0, 0, 0, 0));
                        }
                        else {
                        // single push
                            addMove(list, ENCODE_MOVE(from, to, p, 0, 0, 0, 0, 0));
                        // double push
                            if(from >= a7 && from <= h7){
                                to = from + 16;
                                if(!GET_BIT(occupancies[both], to)){
                                    addMove(list, ENCODE_MOVE(from, to, p, 0, 0, 1, 0, 0));
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
                            addMove(list, ENCODE_MOVE(from, to, p, q, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, r, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, b, 1, 0, 0, 0));
                            addMove(list, ENCODE_MOVE(from, to, p, n, 1, 0, 0, 0));
                        }
                        else{
                            addMove(list, ENCODE_MOVE(from, to, p, 0, 1, 0, 0, 0));
                        }
                        CLEAR_BIT(attacks, to);
                    }

                    if(enpassant != no_sq) {
                        uint64 enpassantAttacks = pawnAttacks[black][from] & (1ULL << enpassant);
                        if(enpassantAttacks) {
                            addMove(list, ENCODE_MOVE(from, enpassant, p, 0, 1, 0, 1, 0));
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
                            addMove(list, ENCODE_MOVE(e8, g8, k, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if(castle & BQ) {
                    //black queenside castle
                    //if all 3 queenside squares are empty
                    if(!GET_BIT(occupancies[both], d8) && !GET_BIT(occupancies[both], c8) && !GET_BIT(occupancies[both], b8)) {
                        //if e8 and d8 do not pass through check
                        if(!isSquareAttacked(e8, white) && !isSquareAttacked(d8, white)){
                            addMove(list, ENCODE_MOVE(e8, c8, k, 0, 0, 0, 0, 1));
                        }
                    }
                }
            }
        }    

        //gen knight moves
        if(side == white ? (piece == N) : (piece == n)) {
            while(bb) {
                from = getLSBIndex(bb);
                //ensure knight only moves to squares not occupied by same color
                attacks = knightAttacks[from] & (side == white ? ~occupancies[white] : ~occupancies[black]);
                while(attacks) {
                    to = getLSBIndex(attacks);
                    //if the to square is occupied by an opponent piece identify it as capture
                    if(GET_BIT(occupancies[!side], to)) addMove(list, ENCODE_MOVE(from, to, piece, 0, 1, 0, 0, 0));
                    //if the to square is empty identify it as a quiet move
                    else addMove(list, ENCODE_MOVE(from, to, piece, 0, 0, 0, 0, 0));
                    CLEAR_BIT(attacks, to);
                }
                CLEAR_BIT(bb, from);
            }
        }
        //gen bishop moves
        if(side == white ? (piece == B) : (piece == b)) {
            while(bb) {
                from = getLSBIndex(bb);
                //ensure bishop only moves to squares not occupied by same color
                attacks = bishopAttacks(occupancies[both], from) & (side == white ? ~occupancies[white] : ~occupancies[black]);
                while(attacks) {
                    to = getLSBIndex(attacks);
                    //if the to square is occupied by an opponent piece identify it as capture
                    if(GET_BIT(occupancies[!side], to)) addMove(list, ENCODE_MOVE(from, to, piece, 0, 1, 0, 0, 0));
                    //if the to square is empty identify it as a quiet move
                    else addMove(list, ENCODE_MOVE(from, to, piece, 0, 0, 0, 0, 0));
                    CLEAR_BIT(attacks, to);
                }
                CLEAR_BIT(bb, from);
            }
        }
        //gen rook moves
        if(side == white ? (piece == R) : (piece == r)) {
            while(bb) {
                from = getLSBIndex(bb);
                //ensure rook only moves to squares not occupied by same color
                attacks = rookAttacks(occupancies[both], from) & (side == white ? ~occupancies[white] : ~occupancies[black]);
                while(attacks) {
                    to = getLSBIndex(attacks);
                    //if the to square is occupied by an opponent piece identify it as capture
                    if(GET_BIT(occupancies[!side], to)) addMove(list, ENCODE_MOVE(from, to, piece, 0, 1, 0, 0, 0));
                    //if the to square is empty identify it as a quiet move
                    else addMove(list, ENCODE_MOVE(from, to, piece, 0, 0, 0, 0, 0));
                    CLEAR_BIT(attacks, to);
                }
                CLEAR_BIT(bb, from);
            }
        }
        //gen queen moves
        if(side == white ? (piece == Q) : (piece == q)) {
            while(bb) {
                from = getLSBIndex(bb);
                //ensure queen only moves to squares not occupied by same color
                attacks = queenAttacks(occupancies[both], from) & (side == white ? ~occupancies[white] : ~occupancies[black]);
                while(attacks) {
                    to = getLSBIndex(attacks);
                    //if the to square is occupied by an opponent piece identify it as capture
                    if(GET_BIT(occupancies[!side], to)) addMove(list, ENCODE_MOVE(from, to, piece, 0, 1, 0, 0, 0));
                    //if the to square is empty identify it as a quiet move
                    else addMove(list, ENCODE_MOVE(from, to, piece, 0, 0, 0, 0, 0));
                    CLEAR_BIT(attacks, to);
                }
                CLEAR_BIT(bb, from);
            }
        }

        //gen king moves
        if(side == white ? (piece == K) : (piece == k)) {
            while(bb) {
                from = getLSBIndex(bb);
                //ensure king only moves to squares not occupied by same color
                attacks = kingAttacks[from] & (side == white ? ~occupancies[white] : ~occupancies[black]);
                while(attacks) {
                    to = getLSBIndex(attacks);
                    //if the to square is occupied by an opponent piece identify it as capture
                    if(GET_BIT(occupancies[!side], to)) addMove(list, ENCODE_MOVE(from, to, piece, 0, 1, 0, 0, 0));
                    //if the to square is empty identify it as a quiet move
                    else addMove(list, ENCODE_MOVE(from, to, piece, 0, 0, 0, 0, 0));
                    CLEAR_BIT(attacks, to);
                }
                CLEAR_BIT(bb, from);
            }
        }
    }
}

static inline int makeMove(int move, int flag){
    if(flag == all) {
        COPY_BOARD;

        // parse move
        int from = GET_MOVE_SOURCE(move);
        int to = GET_MOVE_TARGET(move);
        int piece = GET_MOVE_PIECE(move);
        int promoted = GET_PROMOTED_PIECE(move);
        int isMoveCapture = GET_MOVE_CAPTURE(move);
        int doublePush = GET_MOVE_DOUBLE_PUSH(move);
        int isMoveEnPassant = GET_MOVE_EN_PASSANT(move);
        int isMoveCastle = GET_MOVE_CASTLE(move);

        // move piece
        CLEAR_BIT(bitboards[piece], from);
        SET_BIT(bitboards[piece], to);

        // handle captures
        if(isMoveCapture) {
            int startPiece, endPiece;
            if(side == white) { startPiece = p; endPiece = k; }
            else { startPiece = P; endPiece = K; }
            for(int pce = startPiece; pce <= endPiece; pce++) {
                if(GET_BIT(bitboards[pce], to)) {
                    CLEAR_BIT(bitboards[pce], to);
                    break;
                }
            }
        }
        
        // handle promotions
        if(promoted) {
            CLEAR_BIT(bitboards[piece], to);
            SET_BIT(bitboards[promoted], to);
        }

        // handle en passant
        if(isMoveEnPassant) {
            (side == white) ? CLEAR_BIT(bitboards[p], to + 8) 
                            : CLEAR_BIT(bitboards[P], to - 8);
        }
        isMoveEnPassant = no_sq;

        // handle double pawn push
        if(doublePush) {
            (side == white) ? (enpassant = to + 8)  // update global enpassant variable
                            : (enpassant = to - 8);
        }

        // handle castling
        if(isMoveCastle) {
            switch (to) {
            case g1:
                SWAP_BITS(bitboards[R], h1, f1); break;
            case c1:
                SWAP_BITS(bitboards[R], a1, d1); break;
            case g8:
                SWAP_BITS(bitboards[r], h8, f8); break;
            case c8:
                SWAP_BITS(bitboards[r], a8, d8); break;
            default:
                break;
            }
        }

        // update castling rights
        castle &= castleUpdate[from];
        castle &= castleUpdate[to];

        // update occupancies
        // reinitializing from scratch
        // TODO: optimize this
        occupancies[white] = 0ULL;
        occupancies[black] = 0ULL;
        occupancies[both] = 0ULL;
        for(int pce = P; pce <= K; pce++) {
            occupancies[white] |= bitboards[pce];
            occupancies[black] |= bitboards[pce + 6];
        }
        occupancies[both] = occupancies[white] | occupancies[black];

        // change side to move
        side ^= 1;
        
        //TODO: review
        // ensure king is not in check
        if(isSquareAttacked((side == white ? getLSBIndex(bitboards[k]) : getLSBIndex(bitboards[K])), side)) {
            TAKE_BACK;
            return 0;
        }
        return 1;
    } else {
        if(GET_MOVE_CAPTURE(move)) makeMove(move, all);
        else return 0;
    }
}

static inline int countMoves(char* fen) {
    parseFen(fen);
    moveList list;
    generateMoves(&list);
    return list.count;
}