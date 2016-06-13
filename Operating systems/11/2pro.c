#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <wait.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>

int
main(int argc, char **argv)
{
    int maxval, key, n, i;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &maxval);
    int *pid = calloc(n, sizeof(*pid));
    int id_sem = semget(key, n + 1, IPC_CREAT | 0666);
    int id_shm = shmget(key, sizeof(int), IPC_CREAT | 0666);
    int *val = shmat(id_shm, NULL, 0);
    for (i = 0; i < n; i++) {
        if (!(pid[i] = fork())) {
            struct sembuf p = {i, -1, 0};
            struct sembuf v = {i, 1, 0};
            while (1) {
                semop(id_sem, &p, 1);
                printf("%d: %d\n", i, *val);
                fflush(stdout);
                if (*val == maxval) {
                    v.sem_num = n;
                    semop(id_sem, &v, 1);
                    exit(0);
                } else {
                    *val += 1;
                    v.sem_num = ((*val) * (*val)) % n;
                    semop(id_sem, &v, 1);
                }
            }
        }
    }
    struct sembuf v = {0, 1, 0};
    struct sembuf p = {n, -1, 0};
    *val = 0;
    semop(id_sem, &v, 1);
    semop(id_sem, &p, 1);
    for (i = 0; i < n; i++) {
        kill(pid[i], SIGTERM);
    }
    free(pid);
    shmdt(val);
    shmctl(id_shm, IPC_RMID, 0);
    semctl(id_sem, 0, IPC_RMID, 0);
    return 0;
}
