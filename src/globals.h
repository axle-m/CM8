#ifndef GLOBALS_H
#define GLOBALS_H

#include "attackTables.h" // Or wherever uint64 and SMagic are defined
#include "randomizingRoutines.h"
#include "bit.h"
#include "moveGenerator.h"
#include "driver.h"
#include "inputProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"
extern int killerMoves[2][64];
extern int historyMoves[12][64];

#endif