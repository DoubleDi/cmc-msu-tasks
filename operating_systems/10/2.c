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
#include <math.h>
#include <signal.h>

int curr = 0;
int count = 0;

void hndterm(int s)
{
    exit(0);
}

void hndint(int s)
{
    count++;
    if (count == 4) exit(0);
    else {
        printf("%d\n", curr);
        fflush(stdout);
    }
}



int
main(int argc, char * argv[])
{
    int low;
    int high;
    int flag = 0;
    signal(SIGINT, hndint);
    signal(SIGTERM, hndterm);
    scanf("%d %d", &low, &high);
    printf("%d\n", (int)getpid());
    fflush(stdout);
    for(;low < high; low++){
        flag = 0;
        int slow = pow(low, 0.5); 
        for(int i = 2; i <= slow; i++) {
            if (!(low % i)) {
                flag = 1;
                break;
            }
        }
        if (!flag) curr = low;
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}