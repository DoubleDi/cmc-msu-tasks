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
#include <signal.h>
#include <math.h>

enum { BIT_SIZE = 8 };

char symbol = 0;
int count = 0;
int readcount = 0;
int bit;
int pid1, pid2;
FILE *f;

void bit_handler(int s) {
    if (s == SIGIO) {
        exit(0);
    }
    if (s == SIGUSR2) {
        symbol |= 1 << count;
    }
    if (count == 7) {
        putchar(symbol);
        fflush(stdout);
        symbol = 0;
        count = 0;
    } else {
        count++;
    }
    kill(getppid(), SIGALRM);
}

void parent_handler(int s) {
    if (s == SIGALRM) {
        kill(pid2, SIGALRM);
    } else if (s == SIGUSR2) {
        kill(pid2, SIGUSR2);
    } else if (s == SIGUSR1) {
        kill(pid2, SIGUSR1);
    }
}


void read_handler(int s) {
    if (readcount == 0) {
        if ((bit = fgetc(f)) == EOF) {
            kill(pid1, SIGIO);
            exit(0);
        }
        readcount = 8;
    }
    readcount--;
    if (bit & 1) {
        kill(pid1, SIGUSR2);
    } else {
        kill(pid1, SIGUSR1);
    }
    bit >>= 1;
}

int
main(int argc, char *argv[])
{
    signal(SIGUSR1, bit_handler);
    signal(SIGUSR2, bit_handler);
    signal(SIGIO, bit_handler);
    if (!(pid1 = fork())) {
        while(1);
    }
    f = fopen(argv[1], "r");
    signal(SIGALRM, read_handler);
    if (!(pid2 = fork())) {
        while(1);
    }
    signal(SIGUSR1, parent_handler);
    signal(SIGUSR2, parent_handler);
    signal(SIGALRM, parent_handler);
    kill(pid2, SIGALRM);
    wait(NULL);
    wait(NULL);
    return 0;
}
