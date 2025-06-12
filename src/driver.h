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
#include "eval.h"

extern int search_depth;

extern void recalibrate();

extern int playBestMove();
extern int playBestFromFen(char *fen);



extern uint64 unix_time_ms();
extern void oneVsOne();
extern void init();
extern void cleanup();
#endif