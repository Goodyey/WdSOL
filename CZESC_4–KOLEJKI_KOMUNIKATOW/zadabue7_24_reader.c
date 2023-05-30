/* kolejki komunikatów – msg_reader.c */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// struktura kolejki komunikatów
struct msg_buffer {
    long msg_type;
    char msg_text[50];
} message; 

int main() {
    key_t key;
    int msgid;

    key = 1234;
    // lub ftok do wygenerowania unikalnego klucza key
    //key = ftok("msg_reader.c", 2020);

    // msgget tworzy kolejkę komunikatów
    // i zwraca jej identyfikator
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv – odbieramy wiadomość
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // wyświetlamy wiadomość
    printf("\033[1;31m"); /* drukujemy wiadomość na czerwono */
    printf("Data Received is : %s\n", message.msg_text);
    printf("\033[0m"); /* powracamy do domyślnych kolorów */

    // kasujemy kolejkę komunikatów
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
