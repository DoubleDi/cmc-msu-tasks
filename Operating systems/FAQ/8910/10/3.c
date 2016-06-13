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

    int
    main(int argc, char * argv[])
    {
        int pfd[2];
        int pid, status;
        int last_cmd = 0;
        for (int i = 1; i < argc ; i++) {
            if (i != argc - 1) {
                pipe(pfd);
            }
            if (!(pid = fork())) {
                if (i != argc - 1) {
                    dup2(pfd[1], 1);
                    close(pfd[1]);
                }
                if (i != 1) {
                    dup2(last_cmd, 0);
                    close(last_cmd);
                }
                close(pfd[0]);
                execlp(argv[i], argv[i], NULL);
                exit(1);
            } else {
                last_cmd = pfd[0];
                close(pfd[1]);
                wait(&status);
                if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                    exit(1);
                }
            }
        }
        return 0;
    }