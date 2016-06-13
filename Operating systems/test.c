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


void hnd(int s) {
    printf("process %d terminated\n", (int)getpid());
    exit(0);
}

int
main(int argc, char **argv) {
int pid, status;
char **args = malloc((argc - 2) * sizeof(char *));
signal(SIGALRM, hnd);
for (int i = 0; i < argc - 2; i++) {
    args[i] = malloc(10 * sizeof(char));
    strcpy(args[i], argv[i+2]);
}
if (!(pid = fork())) {
	execvp(argv[2], args);
}
alarm(atoi(argv[1]));
wait(&status);
alarm(0);
if (WIFSIGNALED(status)) {
	printf("process %d signalled by %d\n", pid, WTERMSIG(status));
} else {
	printf("process %d exited with code %d\n", pid, WEXITSTATUS(status));
}
	return 0;
}
