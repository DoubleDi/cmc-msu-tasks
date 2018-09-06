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
#include <sys/wait.h>

enum { MAX_L = 1000 };

int
main(int argc, const char *argv[])
{
    int s_addr = 0, f_addr = 0, f_size = 0, s_size = 0, sum = 0;
    char f_let, s_let;
    char f_di, s_di;
    char str[MAX_L];
    if (!fgets(str, sizeof(str), stdin)) {
        printf("%d", sum);
        return 0;
    }
    sscanf(str, "%c%c %x %d\n", &f_let, &f_di, &f_addr, &f_size);
    while (fgets(str, sizeof(str), stdin)) {
        sscanf(str, "%c%c  %x %d\n", &s_let, &s_di,  &s_addr, &s_size);
        if (f_let == 'W' && s_let == 'R' &&
        s_addr == f_addr && s_size == f_size) {
            sum += atoi(argv[3]);
            s_let = 'B';
        } else if (f_let != 'B') {
            if (f_let == 'R') {
                sum += atoi(argv[1]);
            } else if (f_let == 'W') { 
                sum += atoi(argv[2]);
            }
        }
        f_let = s_let;
        f_addr = s_addr;
        f_size = s_size;
    }
    if (f_let != 'B') {
        if (f_let == 'R') {
            sum += atoi(argv[1]);
        } else if (f_let == 'W') {
            sum += atoi(argv[2]);
        }
    }
    printf("%d", sum);
    return 0;
}
