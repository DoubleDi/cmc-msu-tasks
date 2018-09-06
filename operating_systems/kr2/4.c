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

int
main(int argc, const char *argv[])
{
    int a, pid;
    int fd = open(argv[2], O_CREAT | O_TRUNC, 0777);
    close(fd);
    int a0 = atoi(argv[3]);
    int d = atoi(argv[4]);
    int p_num = atoi(argv[1]);
    int num = atoi(argv[5]);
    for (int i = 0; i < p_num; i++) {
        if (!(pid = fork())) {
            fd = open(argv[2], O_WRONLY);
            for (int k = 0; k < num; k++) {
                a = (k * p_num + i) * d + a0; 
                lseek(fd, sizeof(a) * (k * p_num + i), SEEK_SET);
                write(fd, &a, sizeof(a));
            }
            close(fd);
            exit(0);
        }
    }
    while(wait(NULL) > 0);
    return 0;
}