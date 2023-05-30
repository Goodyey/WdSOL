/* kolejki komunikatów wersja rodzic-potomek */
#ifdef __linux
char os[50] = "Apollo 13 successfully landed on the moon";
#else
char os[50] = "Houston, we have a problem";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFSIZE 49

// struktura dla kolejki komunikatów
struct msg_buffer {
    long msg_type;
    char msg_text[50];
};

int main() {
    key_t key;
    int msgid;
    char buf[BUFSIZ];

    /* utworzenie kolejki komunikatów */
    key = 1234;
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    int pid = fork();
    if (pid == 0) { /* proces potomny */
        /* wysłanie wiadomości do kolejki */
        struct msg_buffer message;
        message.msg_type = 1;
        strcpy(message.msg_text, os);
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        system("ipcs -q | head -3");
        sprintf(buf, "ipcs -q | grep %d", msgid);
        system(buf);
    } else { /* proces rodzic */
        sleep(3);
        /* odczytujemy wiadomość */
        struct msg_buffer received_message;
        if (msgrcv(msgid, &received_message, sizeof(received_message), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("\033[1;31m"); /*drukujemy wiadomość na czerwono*/
        /* wyświetlamy wiadomość */
        printf("Data Received is: %s\n", received_message.msg_text);
        printf("\033[0m"); /* powracamy do domyślnych kolorów */

        // kasujemy kolejkę komunikatów
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }
    return 0;
}
