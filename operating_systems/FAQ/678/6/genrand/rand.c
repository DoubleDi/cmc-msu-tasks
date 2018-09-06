#include "rand.h"

long rand_range(long low, long high) {
    double ran = rand() / (RAND_MAX + 1.0);
    return (long)(ran * (high - low)) + low;
}