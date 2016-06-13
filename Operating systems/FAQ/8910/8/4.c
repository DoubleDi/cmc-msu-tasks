#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>

enum { DEC = 10 };

int 
main(int argc, const char * argv[])
{
    int pid;
    int pfd12[2];
    int pfd21[2];
    long end = strtol(argv[1], NULL, DEC);
    long num = 1;
    if (pipe(pfd12) != 0) {
        return 1;
    }
    if (pipe(pfd21) != 0) {
        return 1;
    }
    FILE *read1 = fdopen(pfd21[0], "r");
    FILE *read2 = fdopen(pfd12[0], "r");
    FILE *write1 = fdopen(pfd12[1],  "w");
    FILE *write2 = fdopen(pfd21[1],  "w");
    if (!(pid = fork())) {
        //son1
        while (num < end) {
            printf("1 %ld\n", num);
            fflush(stdout);
            num++;
            fprintf(write1, "%ld ", num);
            fflush(write1);
            fscanf(read1, "%ld", &num);
        }
    } else {
        if (!(pid = fork())) {
            //son2
            while (num < end) {
                fscanf(read2, "%ld", &num);
                if (num < end) {
                    printf("2 %ld\n", num);
                    fflush(stdout);
                }
                num++;
                fprintf(write2, "%ld ", num);
                fflush(write2);
            }
        } else {
            //father
            wait(NULL);
            wait(NULL);
            puts("Done");
        }
    }
    return 0;
}