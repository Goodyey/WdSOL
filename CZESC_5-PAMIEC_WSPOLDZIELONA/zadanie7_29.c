/* pamięć współdzielona – program serwera */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSIZE 49

int main() {
    char c;
    int shmid;
    key_t key;
    char *shm, *msg;
    int err;

    key = 1234;
    /* utworzenie segmentu pamięci współdzelonej */
    if ((shmid = shmget(key, BUFSIZE, IPC_CREAT | 0666)) < 0) {
        perror("serwer – błąd shmget: ");
        exit(1);
    } else {
        printf("Serwer: utworzono segment pamięci współdzielonej o kluczu: %d (hexadecimal: %#08x) i ID: %d\n" , key, key, shmid);
    }
    
    /* dołączanie segment pamięci współdzielonej */
    if ((... shmat(...)) == ...) {
        perror("serwver – błąd shmat: ");
        exit(2);
    } else {
        printf("Serwer: segment pamięci współdzielonej dołączono pod adresem: %p\n" , shm);
    }

    /* Zapis danych do pamięci współdzielonej dla klienta */
    msg = shm;
    strcpy(msg,"Czy potrafisz tak współdzielić pamięć z przyjacielem jak ja?");

    /* odłączenie bloku pamięci współdzielonej */
    if ((err = shmdt(shm)) == -1) {
        perror("serwer – błąd shmdt: ");
        exit(1);
    }

    exit(0);
}
