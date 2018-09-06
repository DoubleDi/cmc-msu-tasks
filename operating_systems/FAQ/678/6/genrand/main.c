#include "rand.h"

enum { DEC = 10 };

int
main(int argc, const char * argv[])
{
    long count = strtoll(argv[1], NULL, DEC);
    long low = strtoll(argv[2], NULL, DEC);
    long high = strtoll(argv[3], NULL, DEC);
    long seed = strtoll(argv[4], NULL, DEC);
    srand(seed);
    for (int i = 0; i < count; i++) {
        printf("%ld\n", rand_range(low, high));
    }
}
