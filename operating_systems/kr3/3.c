
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
    char str[1024];
    int i;
    int gen_num = atoi(argv[1]);
    int gen1 = atoi(argv[2]);
    int gen2 = atoi(argv[3]);
    pipe(pfd);
    for (i = 1; i <= gen_num; i++) {
        if (fork()) {
            //parent;
            if (i - 1 == gen1) {
                close(pfd[0]);
                FILE *f = fopen(argv[4], "r");
                while (fgets(str, sizeof(str), f)) {
                    write(pfd[1], str, sizeof(str));
                }
                close(pfd[1]);
                fclose(f);
            } else if (i - 1 == gen2) {
                close(pfd[1]);
                while (read(pfd[0], str, sizeof(str))) {
                    printf("%s", str);
                    fflush(stdout);
                }
                close(pfd[0]);
            } else {
                close(pfd[1]);
                close(pfd[0]);
            }
            while (wait(NULL) != -1);
            exit(0);
        }
        //son
    }

    if (gen_num == gen1) {
        close(pfd[0]);
        FILE *f = fopen(argv[4], "r");
        while (fgets(str, sizeof(str), f)) {
            write(pfd[1], str, sizeof(str));
        }
        close(pfd[1]);
        fclose(f);
    } else if (gen_num == gen2) {
        close(pfd[1]);
        while (read(pfd[0], str, sizeof(str))) {
            printf("%s", str);
            fflush(stdout);
        }
        close(pfd[0]);
    } else {
        close(pfd[1]);
        close(pfd[0]);
    }

    exit(0);
    return 0;
}
