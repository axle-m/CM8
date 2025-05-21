#include <stdio.h>
#include "bit.h"

const U64 NOT_A;
/* not A
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
    0 1 1 1 1 1 1 1
*/

const U64 NOT_B;
/* not B
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
    1 0 1 1 1 1 1 1
*/

const U64 NOT_H;
/* not H
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
    1 1 1 1 1 1 1 0
*/
const U64 NOT_G;
/* not G
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
    1 1 1 1 1 1 0 1
*/

// const U64 NOT_AB = NOT_A & NOT_B;
// const U64 NOT_HG = NOT_H & NOT_G;
// const U64 NOT_AH = NOT_A & NOT_H;
// const U64 NOT_BH = NOT_B & NOT_H;

U64 maskPawnAttacks(int pos, int side);