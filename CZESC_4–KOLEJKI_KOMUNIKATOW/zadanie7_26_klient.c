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
    int number;
    int sum;

    key = ftok("serwer26.c", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    sum = 0;
    while (1) {
        printf("Enter a number (0 to finish): ");
        scanf("%d", &number);

        message.mtype = M_DATA;
        message.data = number;
        msgsnd(msgid, &message, sizeof(message.data), 0);
    
        sum += number;

        if (number == 0) {
            break;
        }
    }

    message.mtype = M_END;
    msgsnd(msgid, &message, sizeof(message.data), 0);

    msgrcv(msgid, &message, sizeof(message.data), M_RESULT, 0);

    printf("Sum: %d\n", message.data);

    return 0;
}
