/* kolejki komunikatów – msg_writer.c */
#ifdef __linux
char os[50] = "Apollo 13 successfully landed on the moon";
#else
char os[50] = "Houston, we have a problem";
#endif

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// struktura dla kolejki komunikatów
// definicja msgbuf znajduje się w sys/msg.h
struct msgbuf {
    long msg_type;
    char msg_text[50];
} message;

int main() {
    key_t key;
    int msgid;
    size_t buf_length;

    key = 1234;
    // poprawniej jest użyć funkcji ftok do wygenerowania unikalnego klucza
    // key = ftok("msg_writer.c", 2020);

    // msgget tworzy kolejkę komunikatów
    // i zwraca jej identyfikator
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    // message to send
    strcpy(message.msg_text,os);
    //strcpy(message.msg_text,"Apollo 13: The Earth is flat!");

    // send message
    msgsnd(msgid, &message, sizeof(message), 0);

    return 0;
}
