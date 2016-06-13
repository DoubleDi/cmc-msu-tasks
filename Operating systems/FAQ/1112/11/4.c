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
#include <stdatomic.h>

enum { LIMIT = 10 };

int
main(int argc, char * argv[])
{
    int count = atoi(argv[1]);
    key_t key = atoi(argv[2]);
    int iter_count = atoi(argv[3]);
    int seed = atoi(argv[4]);
    int elem, index1, index2;
    int shmid = shmget(key, count * sizeof(elem), IPC_CREAT | 0666);
    int semid = semget(key, 2, IPC_CREAT | 0666);
    double ran;
    int *num_arr = (int *)shmat(shmid, NULL, 0);
    for(int i = 0; i < count; i++) {
        scanf("%d", &elem);
        num_arr[i] = elem;
    }
    semctl(semid, 0, SETVAL, 1);
    if (!fork()) {
        srand(seed);
        for (int k = 0; k < iter_count; k++) {
            semop(semid, (struct sembuf []){{ 0, -1, SEM_UNDO }}, 1);
            ran = rand() / (RAND_MAX + 1.0);
            index1 = (int)(ran * count);
            ran = rand() / (RAND_MAX + 1.0);
            index2 = (int)(ran * count);
            ran = rand() / (RAND_MAX + 1.0);
            elem = (int)(ran * LIMIT);
            operation(num_arr, index1, index2, elem);
            semop(semid, (struct sembuf []) {{ 1, 1, SEM_UNDO }}, 1);
        }
        exit(0);
    }

    if (!fork()) {
        int hole_summ = 0;
        for (int k = 0; k < iter_count; k++) {
            semop(semid, (struct sembuf []){{ 1, -1, SEM_UNDO }}, 1);
            hole_summ += summ(num_arr, count);
            semop(semid, (struct sembuf []){{ 0, 1, SEM_UNDO }}, 1);
        }
        printf("%d\n", hole_summ);
        fflush(stdout);
        exit(0);
    }
    while (wait(NULL) != -1);
    shmdt(num_arr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}
