#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define M_DATA 1
#define M_END 2
#define M_RESULT 3

struct msgbuf {
    long mtype;
    int data;
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;
    int sum = 0;

    key = ftok("serwer26.c", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        msgrcv(msgid, &message, sizeof(message.data), M_DATA, 0);
        sum += message.data;
        if (message.mtype == M_END) {
            break;
        }
    }

    message.mtype = M_RESULT;
    message.data = sum;
    msgsnd(msgid, &message, sizeof(message.data), 0);

    return 0;
}
