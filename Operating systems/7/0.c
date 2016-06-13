#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>



int
main(void)
{
    int pid;
    printf("me ");
    //fflush(stdout); с ней происходит без буферизации
    if ((pid = fork()) > 0) {
        printf("parent: %d, parent of: %d\n", getpid(), getppid());
    } else {
        printf("son: %d, parent of: %d\n", getpid(), getppid());
        //printf("%d", 1/0); segfaulft
        exit(0);
    }
    int stat;
    int pid2 = wait(&stat);
    if (WIFEXITED(stat) && !WEXITSTATUS(stat)) {
        puts("good exit");
    } else {
        puts("bad exit");
        printf("%d %d", (int)WEXITSTATUS(stat), (int)WTERMSIG(stat));
    }
    return 0;
}
