#include "attackTables.h" 
#include "randomizingRoutines.h"
#include "bit.h"
#include "moveGenerator.h"
#include "driver.h"
#include "inputProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boardState.h"
#include "eval.h"
#include "globals.h"

int killerMoves[2][64];
int historyMoves[12][64];
