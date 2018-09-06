#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

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
        double ran = rand() / (RAND_MAX + 1.0);
        printf("%ld\n", (int)(ran * (high - low)) + low);
    }
}
