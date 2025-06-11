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

int search_depth;

void recalibrate();

int playBestMove();
int playBestFromFen(char *fen);

uint64 unix_time_ms();
void oneVsOne();
void init();
void cleanup();
#endif