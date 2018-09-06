
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
main(int argc, char *argv[])
{
    int pfd[2];
    int status;
    pipe(pfd);
    if (!fork()) {
        dup2(pfd[1], 1);
        close(pfd[1]);
        close(pfd[0]);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    close(pfd[1]);
    if (!fork()) {
        int fd = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0666);
        dup2(pfd[0], 0);
        dup2(fd, 1);
        close(pfd[0]);
        close(fd);
        if (!fork()) {
            close(pfd[0]);
            execlp(argv[2], argv[2], NULL);
            exit(1);
        } else {
            wait(&status);
            if WIFSIGNALED(status) exit(0);
            if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                exit(0);
            }
        }
        if (!fork()) {
            close(pfd[0]);
            execlp(argv[3], argv[3], NULL);
            exit(1);
        } else {
            wait(&status);
            if WIFSIGNALED(status) exit(0);
            if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                exit(0);
            }
        }
    } else {
        close(pfd[0]);
    }
    while (wait(NULL) != -1);
    return 0;
}
