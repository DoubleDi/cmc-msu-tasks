#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

enum { DEC = 10 };
struct msgbuf {
    long mtype;
    char mtext[1024];
};

int
main(int argc, char const *argv[]) {
    int pid;
    key_t key1 = ftok("sync", 123123);
    int msgid1 = msgget(key1, IPC_CREAT | 0666);
    key_t key2 = ftok("sync", 456456);
    int msgid2 = msgget(key2, IPC_CREAT | 0666);
    int num = 1;
    long end = strtol(argv[1], NULL, DEC);
    if (!(pid = fork())) {
        struct msgbuf rcv;
        struct msgbuf snd;
        while (num < end) {
            printf("1 %d\n", num);
            fflush(stdout);
            usleep(100);
            snd.mtype = 1;
            sprintf(snd.mtext, "%d", num + 1);
            msgsnd(msgid2, &snd, sizeof(snd.mtext), 0);
            msgrcv(msgid1, &rcv, sizeof(rcv.mtext), 0, 0);
            rcv.mtext[strlen(rcv.mtext)] = 0;
            sscanf(rcv.mtext, "%d", &num);
        }
        sprintf(snd.mtext, "%d", -1);
        msgsnd(msgid2, &snd, sizeof(snd.mtext), 0);
        exit(0);
    } else {
        if (!(pid = fork())) {
            struct msgbuf rcv;
            struct msgbuf snd;
            while (num < end) {
                msgrcv(msgid2, &rcv, sizeof(rcv.mtext), 0, 0);
                rcv.mtext[strlen(rcv.mtext)] = 0;
                sscanf(rcv.mtext, "%d", &num);
                if(num == -1) exit(0);
                if (num < end) {
                    printf("2 %d\n", num);
                    fflush(stdout);
                }
                snd.mtype = 1;
                sprintf(snd.mtext, "%d", num + 1);
                msgsnd(msgid1, &snd, sizeof(snd.mtext), 0);
            }
            exit(0);
        } else {
            //father
            wait(NULL);
            wait(NULL);
            msgctl(msgid1, IPC_RMID, 0);
            msgctl(msgid2, IPC_RMID, 0);
            puts("Done");
            fflush(stdout);
        }
    }
    return 0;
}