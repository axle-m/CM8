#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "attackTables.h"
#include "randomizingRoutines.h"
#include "inputProcessor.h"

void init() {
    initAttackTables();
    initRandomizingRoutines();
}
