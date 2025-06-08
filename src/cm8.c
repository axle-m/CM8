#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    int move = ENCODE_MOVE(e7, e8, p, N, 1, 0, 0, 0);
    
    moveList list;
    initMoveList(&list);
    printf("move count: %d\n", list.count);
    addMove(&list, move);
    printMoveList(&list);

    cleanup();
    return 0;
}