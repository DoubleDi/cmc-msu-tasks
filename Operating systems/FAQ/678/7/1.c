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
    int pid = 0, stat;
    int a;
    while (scanf("%d", &a) > 0) {
        if ((pid = fork()) > 0) break;
    }
    waitpid(pid, &stat, 0);
    if (pid != 0) {
        printf("%d\n", a);
        exit(0);
    }
    return 0;
}

