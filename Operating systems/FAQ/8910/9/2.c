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
main(int argc, const char * argv[])
{
    // 1 - cmd1; 2 - cmd2; 3 - cmd3 ; 4 - file1 ; 5 - file2;
    int pfd[2];
    int status, fdin, fdout;
    pipe(pfd);
    if(!fork()) {
        close(pfd[0]);
        if (fork()) {
            wait(&status);
            if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                exit(1);
            }
        } else {
            fdin = open(argv[4], O_RDONLY);
            dup2(fdin, 0);
            dup2(pfd[1], 1);
            close(pfd[1]);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        if (fork()) {
            close(pfd[1]);
            wait(&status);
        } else {
            dup2(pfd[1], 1);
            close(pfd[1]);
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        exit(0);
    } else  if (fork()) {
        close(pfd[1]);
        close(pfd[0]);
        while (wait(NULL) != -1);
    } else {
        close(pfd[1]);
        fdout = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
        dup2(pfd[0], 0);
        dup2(fdout, 1);
        close(pfd[0]);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    return 0;
}