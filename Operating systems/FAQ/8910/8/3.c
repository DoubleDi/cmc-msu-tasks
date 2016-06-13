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

int 
main(void)
{
    int pid;
    int status;
    int pfd[2];
    time_t tm = time(NULL);
    struct tm *timestr;
    if (pipe(pfd) != 0) {
        return 1;
    }
    
    if (!(pid = fork())) {
        //son
        if (read(pfd[0], &tm, sizeof(tm)) < 0) {
            return 1;
        }
        if (!(pid = fork())) {
            //grandson
            if (read(pfd[0], &tm, sizeof(tm)) < 0) {
                return 1;
            }
            if (!(pid = fork())) {
                //great grandson
                if (read(pfd[0], &tm, sizeof(tm)) < 0) {
                    return 1;
                }
                timestr = localtime(&tm);
                printf("S:%02d\n", timestr->tm_sec);
            } else {
                waitpid(pid, &status, 0);
                timestr = localtime(&tm);
                printf("M:%02d\n", timestr->tm_min);
            }
        } else {
            waitpid(pid, &status, 0);
            timestr = localtime(&tm);
            printf("H:%02d\n", timestr->tm_hour);
        }
    } else {
        if (write(pfd[1], &tm, sizeof(tm)) < 0) {
            return 0;
        }
        if (write(pfd[1], &tm, sizeof(tm)) < 0) {
            return 0;
        }
        if (write(pfd[1], &tm, sizeof(tm)) < 0) {
            return 0;
        }
    }
    waitpid(pid, &status, 0);
    return 0;
}