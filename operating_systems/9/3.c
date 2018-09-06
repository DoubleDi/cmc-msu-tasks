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

int flag = 0;

void handlersq(int s)
{
    flag = 1;
}


void handlerrev(int s)
{
    flag = 0;    
}

int
main(void) 
{
    int num;
    signal(SIGUSR1, handlerrev);
    signal(SIGUSR2, handlersq);
    printf("%d\n", getpid());
    fflush(stdout);
    while(scanf("%d", &num) == 1) {
        if (!flag) {
            //rev;
            printf("%d\n", -num);
            fflush(stdout);
        } else {
            //sqr
            printf("%d\n", num * num);
            fflush(stdout);
        }
    }
    
    return 0;
}