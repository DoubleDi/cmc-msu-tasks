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
    int pid1, pid2;
    int num;
    key_t key1 = ftok("sync", 123123);
    int msgid1 = msgget(key1, IPC_CREAT | 0666);
    key_t key2 = ftok("sync", 456456);
    int msgid2 = msgget(key2, IPC_CREAT | 0666);
    struct msgbuf rcv;
    struct msgbuf snd;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    if (!(pid1 = fork())) {
        while (1) {
            msgrcv(msgid2, &rcv, sizeof(rcv.mtext), 0, 0);
            rcv.mtext[strlen(rcv.mtext)] = 0;
            sscanf(rcv.mtext, "%d", &num);
            if(num == -1) {
                exit(0);
            } else {
                if (scanf("%d", &num) > 0) {
                    printf("1 %d\n", num);
                    snd.mtype = 1;
                    num = 1;
                    sprintf(snd.mtext, "%d", num);
                    msgsnd(msgid1, &snd, sizeof(snd.mtext), 0);
                } else {
                    snd.mtype = 1;
                    num = -1;
                    sprintf(snd.mtext, "%d", num);
                    msgsnd(msgid1, &snd, sizeof(snd.mtext), 0);
                    exit(0);
                }
            }
        }
    } else {
        if (!(pid2 = fork())) {
            while (1) {
                msgrcv(msgid1, &rcv, sizeof(rcv.mtext), 0, 0);
                rcv.mtext[strlen(rcv.mtext)] = 0;
                sscanf(rcv.mtext, "%d", &num);
                if(num == -1) {
                    exit(0);
                } else {
                    if (scanf("%d", &num) > 0) {
                        printf("2 %d\n", num);
                        snd.mtype = 1;
                        num = 1;
                        sprintf(snd.mtext, "%d", num);
                        msgsnd(msgid2, &snd, sizeof(snd.mtext), 0);
                    } else {
                        snd.mtype = 1;
                        num = -1;
                        sprintf(snd.mtext, "%d", num);
                        msgsnd(msgid2, &snd, sizeof(snd.mtext), 0);
                        exit(0);
                    }
                }
            }
        } else {
            //father
            snd.mtype = 1;
            num = 1;
            sprintf(snd.mtext, "%d", num);
            msgsnd(msgid2, &snd, sizeof(snd.mtext), 0);
            wait(NULL);
            wait(NULL);
            msgctl(msgid1, IPC_RMID, 0);
            msgctl(msgid2, IPC_RMID, 0);
        }
    }
    return 0;
}
