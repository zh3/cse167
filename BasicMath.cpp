#include <stdlib.h>
#include <time.h>
#include "BasicMath.h"

const double BasicMath::PI = acos(-1.0);

void BasicMath::randomInit(unsigned int seed) {
    srand(seed);
}

int BasicMath::randomRange(unsigned int min, unsigned int max) {
    int r = (rand() % (max - min + 1)) + min;
    return r;
}