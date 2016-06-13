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

enum { LIMIT = 10 };


int
main(int argc, char * argv[])
{
    int count = atoi(argv[1]);
    key_t key = ftok("sync", 123123);
    // key_t key = atoi(argv[2]);
    int nproc = atoi(argv[3]);
    int iter_count = atoi(argv[4]);
    int elem, index1, index2;
    int shmid = shmget(key, count * sizeof(elem), IPC_CREAT | 0666);
    double ran;
    int semid = semget(key, count, IPC_CREAT | 0666);
    int *num_arr = (int *)shmat(shmid, NULL, 0);
    unsigned short *arr = calloc(count, sizeof(*arr));
    for(int i = 0; i < count; i++) {
        scanf("%d", &elem);
        num_arr[i] = elem;
        arr[i] = 1;
    }

    semctl(semid, 0, SETALL, arr);
    for(int i = 0; i < nproc; i++) {
        if (!fork()) {
            srand(atoi(argv[i + 5]));
            for (int k = 0; k < iter_count; k++) {
                ran = rand() / (RAND_MAX + 1.0);
                index1 = (int)(ran * count);
                ran = rand() / (RAND_MAX + 1.0);
                index2 = (int)(ran * count);
                ran = rand() / (RAND_MAX + 1.0);
                elem = (int)(ran * LIMIT);
                if (index1 != index2) {
                    semop(semid, (struct sembuf []){{ index1, -1, SEM_UNDO },
                    { index2, -1, SEM_UNDO }}, 2);
                } else {
                    semop(semid, (struct sembuf [])
                    {{ index1, -1, SEM_UNDO }}, 1);
                }
                operation(num_arr, index1, index2, elem);
                if (index1 != index2 ){
                    semop(semid, (struct sembuf []){{ index1, 1, SEM_UNDO },
                    { index2, 1, SEM_UNDO }}, 2);
                } else {
                    semop(semid, (struct sembuf [])
                    {{ index1, 1, SEM_UNDO }}, 1);
                }
            }
            exit(0);
        }
    }
    while (wait(NULL) != -1);
    for (int j = 0; j < count; j++) {
        printf("%d ", num_arr[j]);
    }
    fflush(stdout);
    shmdt(num_arr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, IPC_RMID, 0);
    return 0;
}
