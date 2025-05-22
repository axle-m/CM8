#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int squareToPos(char *square) {
    int file = square[0] - 'a';
    int rank = 7 - (square[1] - '1');
    return rank * 8 + file;
}