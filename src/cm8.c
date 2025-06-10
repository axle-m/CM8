#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "driver.h"
#include "boardState.h"

int main(int argc, char *argv[]) {
    printf("cm8 engine\n");
    init();

    parseFen("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
    printBoard();
    printf("score: %d\n", evaluate());

    cleanup();
    return 0;
}