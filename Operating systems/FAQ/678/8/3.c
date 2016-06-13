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


int execute(char * proc) 
{ 
    int flag;
    int pid;
    int status;
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
main(int argc, char *argv[])
{
    int flag;
    flag = execute(argv[1]);
    if (flag) {
        flag = execute(argv[2]);
    } else {
        flag = 0;
    }
    if (!flag) {
        flag = execute(argv[3]);
    } else {
        flag = 1;
    }
    if (flag > 1) flag = 1;
    return flag;
}
