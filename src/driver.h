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

int getBestMove();
void oneVsOne();
void init();
void cleanup();
uint64 unix_time_ms();

#endif