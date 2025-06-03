#include <stdio.h>
#include <stdlib.h>

#include "bit.h"
#include "driver.h"

unsigned int state = 1804289383;

unsigned int getrand32() {
    unsigned int x = state;

    //XOR shift algorithm
    x ^= (x << 13);
    x ^= (x >> 17);
    x ^= (x << 5);
    state = x;
    return x;
}

U64 getrand64() {
    U64 a, b, c, d;
    a = getrand32() & 0xFFFF;
    b = getrand32() & 0xFFFF;
    c = getrand32() & 0xFFFF;
    d = getrand32() & 0xFFFF;

    return a | (b << 16) | (c << 32) | (d << 48);
}

U64 genmagic() {
    return getrand64() & getrand64() & getrand64();
}