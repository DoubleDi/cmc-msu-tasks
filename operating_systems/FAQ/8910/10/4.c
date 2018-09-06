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
    int pfd[2];
    int mod = atoi(argv[2]);
    int num, pid;
    long long sum = 0;
    long long limit_sum = atoi(argv[3]);
    pipe(pfd);
    
    if (!fork()) {
        if (!(pid = fork())) {
            read(pfd[0], &pid, sizeof(pid));
            FILE *f = fopen(argv[1], "r");
            while(fscanf(f, "%d", &num) > 0) {
                num %= mod;
                num = (num * num) % mod;
                write(pfd[1], &num, sizeof(num));
            }
            close(pfd[0]);
            close(pfd[1]);
            fclose(f);
            exit(0);
        }
        write(pfd[1], &pid, sizeof(pid));
        write(pfd[1], &pid, sizeof(pid));
        close(pfd[0]);
        close(pfd[1]);
        wait(NULL);
        exit(0);
    }
    wait(NULL);
    if (!fork()) {
        close(pfd[1]);
        read(pfd[0], &pid, sizeof(pid));
        while(read(pfd[0], &num, sizeof(num)) > 0) {
            sum += num;
            if (sum > limit_sum) {
                puts("-1");
                kill(pid, SIGTERM);
                exit(0);
            }
        }
        printf("%lld\n", sum);
        close(pfd[0]);
        exit(0);
    }
    close(pfd[1]);
    close(pfd[0]);
    while (wait(NULL) != -1);
    puts("0");
    return 0;
}