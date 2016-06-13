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
    time_t timefirst = 0, timesecond = 0;
    FILE *f = fopen(argv[1], "r");
    struct tm one = {};
    assert(fscanf(f, "%d/%d/%d %d:%d:%d ", &one.tm_year, &one.tm_mon,
    &one.tm_mday, &one.tm_hour, &one.tm_min, &one.tm_sec) > 0);
    one.tm_isdst = -1;
    one.tm_year -= 1900;
    one.tm_mon--;
    timefirst = mktime(&one);
    while (fscanf(f, "%d/%d/%d %d:%d:%d ", &one.tm_year, &one.tm_mon,
    &one.tm_mday, &one.tm_hour, &one.tm_min, &one.tm_sec) > 0) {
        one.tm_year -= 1900;
        one.tm_mon--;
        one.tm_isdst = -1;
        timesecond = mktime(&one);
        printf("%lld\n", (long long)(timesecond - timefirst));
        timefirst = timesecond;
    }
}
