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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <ctype.h>


enum { SIZE = 1001 };
int pid1 = 0;
int pid2 = 0;
char *str;
FILE *f;
int count = 0;

void hnd1(int s)
{
    char str1[1002];
    if (pid2 == 0) {
        sscanf(str, "%d", &pid2);
    }
    if (fgets(str1, sizeof(str1), f)) {
        count++;
        while (str1[strlen(str1) - 1] == '\n' ||
        isspace(str1[strlen(str1) - 1])) {
            str1[strlen(str1) - 1] = 0;
        }
        sprintf(str, "%s", str1);
        kill(pid2, SIGUSR2);
    } else {
        sprintf(str, "%d", count);
        kill(pid2, SIGABRT);
        exit(0);
    }
}

void hnd2(int s)
{
    printf("%d\n", (int)strlen(str));
    fflush(stdout);
    kill(pid1, SIGUSR1);
}

int
main(int argc, char * argv[])
{
    int shmid;
    key_t key;
    key = atoi(argv[1]);
    shmid = shmget(key, SIZE, IPC_CREAT | 0666);
    str = (char *)shmat(shmid, NULL, 0);
    f = fopen(argv[2], "r");
    signal(SIGUSR1, hnd1);
    signal(SIGUSR2, hnd2);
    if (!(pid1 = fork())) {
        while(1) sleep(1);
    } else {
        if (!(pid2 = fork())) {
            while(1) sleep(1);
        } else {
            sprintf(str,"%d", pid2);
            kill(pid1, SIGUSR1);
            wait(NULL);
            wait(NULL);
            sscanf(str, "%d", &count);
            printf("%d\n", count);
            fclose(f);
            shmdt(str);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }
    return 0;
}
