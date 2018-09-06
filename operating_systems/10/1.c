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

int count = 0;
int n;


int execute(char * file)
{
    int flag;
    int pid;
    int status;
    char proc[1000];
    FILE *f = fopen(file, "r");
    fgets(proc, sizeof(proc), f);
    fclose(f);
    if ((pid = fork())) {
        wait(&status);
        if WIFSIGNALED(status) return 1;
        if WIFEXITED(status) {
        flag = WEXITSTATUS(status);
        } else return 1;
    } else {
        //child
        execlp("/bin/sh", "/bin/sh", "-c", proc, NULL);
        return 1;
    }
    return flag;
}



int
main(int argc, char * argv[])
{
    int res = 0;
    n = atoi(argv[1]);
    for (int i = 2; i < argc; i++) {
        if (!execute(argv[i])) res++;
    }
    printf("%d", res);
    return 0;
}