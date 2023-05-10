#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//podstawowa wersja programu wyświetla cykliczne 3 napisy po naciśnięciu CTRL+C
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[3][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\
n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n",
"Auć - to bolało!\n"};
int nr_napisu=0;

void obsluga_sig_int(int sig) {
    printf(napisy[nr_napisu],getpid(),sig);
    nr_napisu=((nr_napisu + 1) % 3);
}

int main(int argc, char** argv) {
    signal(SIGINT,obsluga_sig_int);

    while (true) {
        printf("Cześć tu proces: %d\n",getpid());
        sleep(1);
    }
}