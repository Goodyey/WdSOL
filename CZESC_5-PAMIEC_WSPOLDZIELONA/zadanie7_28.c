#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define BUFSIZE 1024

int main() {
    int shmid;
    key_t key=1234;
    if ((shmid = shmget(key, BUFSIZE, IPC_CREAT | 0666)) < 0) {
        perror("serwer – błąd shmget: ");
        exit(1);
    } else {
        printf("Serwer: utworzono segment pamięci współdzielonej o kluczu: %d (hexadecimal: %#08x) i ID: %d\n" , key, key, shmid);
    }
    return 0;
}
