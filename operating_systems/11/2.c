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
#include <sys/sem.h>
#include <ctype.h>



int
main(int argc, char * argv[])
{
    long long nproc = atoi(argv[1]);
    key_t key = ftok("max_lalka", 123123);
    long long maxval = atoi(argv[3]);
    int *pids= calloc(nproc, sizeof(*pids));
    int pid;
    int shmid = shmget(key, sizeof(maxval), IPC_CREAT | 0666);
    int semid = semget(key, nproc + 1, IPC_CREAT | 0666);
    unsigned short *args = calloc(nproc, sizeof(*args));
    long long *num = (long long *)shmat(shmid, NULL, 0);
    (*num) = 0;
    for (long long i = 0; i < nproc; i++) {
        if (!(pid = fork())) {
            while (1) {
                semop(semid, (struct sembuf[]) {{i, -1, 0}}, 1);
                printf("%lld: %lld\n", i, *num);
                fflush(stdout);
                if ((*num) < maxval) {
                    (*num)++;
                    semop(semid, (struct sembuf[]) {{((*num) * (*num)) % nproc, 1, 0}}, 1);
                } else {
                    semop(semid, (struct sembuf[]) {{nproc, 1, 0}}, 1);
                    exit(0);
                }
            }
        }
        pids[i] = pid;
    }
    semop(semid, (struct sembuf[]) {{0, 1, 0}}, 1);
    semop(semid, (struct sembuf[]) {{nproc, -1, 0}}, 1);
    for (long long i = 0; i < nproc; i++) {
        kill(pids[i], SIGTERM);
    }
    shmdt(num);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, IPC_RMID, 0);
    return 0;
}
