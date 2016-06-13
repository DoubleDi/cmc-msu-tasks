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

long num = 1;
long end;
FILE *fr;
FILE *fw;
int set_pid = 0;
    int pid;



void handler (int s)
{
    if (set_pid == 0) {
        fscanf(fr, "%d", &set_pid);
    }
    fscanf(fr, "%ld", &num);
    if (num < end) {
        printf("%ld %ld\n",2 - (num % 2),  num);
        fflush(stdout);
        num++;
        fprintf(fw, "%ld ", num);
        fflush(fw);
        kill(set_pid, SIGUSR1);
    } else {
        fprintf(fw, "%ld ", num);
        fflush(fw);
        kill(set_pid, SIGUSR1);
        exit(0);
    }
}

int 
main(int argc, const char * argv[])
{
    int pfd[2];
    signal(SIGUSR1, handler);
    end = strtol(argv[1], NULL, DEC);
    pipe(pfd);
    fr = fdopen(pfd[0], "r");
    fw = fdopen(pfd[1],  "w");
    if (!(pid = fork())) {
        //son1
        while(1) pause();
    } else {
        set_pid = pid;
        if (!(pid = fork())) {  
            //son2
            while(1) pause();
        } else {
            //father
            fprintf(fw, "%d ", pid);
            fprintf(fw, "%ld ", num);
            fflush(fw);
            kill(set_pid, SIGUSR1);
            wait(NULL);
            wait(NULL);
            puts("Done");
        }
    }
    return 0;
}