#ifndef inputProcessor
#define inputProcessor

#define empty_board "8/8/8/8/8/8/8/8 b - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "
#define repetitions "2r3k1/R7/8/1R6/8/8/P4KPP/8 w - - 0 40 "
//THIS METHOD IS ONE TO RUN
extern int makePlayerMove(char *move, int promotion, char* fen); //${piece}${from}${to}, ex (Pe2e4, 0), (Pe7e8Q, 1) if move is a promotion pass in 1 as argument, otherwise 0
extern int squareToPos(char square[]);
extern void parseFen(char *fen);
extern void processMove(char *move);
#endif