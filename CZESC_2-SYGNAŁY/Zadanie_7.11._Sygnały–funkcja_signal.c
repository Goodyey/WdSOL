#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//zmodyfikowana wersja programu - po 4-tym naciśnięciu CTRL+C wyświetla napis i kończy działanie
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[3][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\
n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n",
"Auć - to bolało!\n"};
int nr_napisu=0;
int licznik_ctrl_c = 0;

void obsluga_sig_int(int sig) {
    if (sig == SIGINT) {
        licznik_ctrl_c++;
        if (licznik_ctrl_c == 4) {
            printf("Dobrze! Dobrze! Już kończę.\n");
            exit(0);
        }
        printf(napisy[nr_napisu],getpid(),sig);
        nr_napisu=((nr_napisu + 1) % 3);
    }
}

int main(int argc, char** argv) {
    signal(SIGINT,obsluga_sig_int);
    signal(SIGQUIT,SIG_DFL);

    while (true) {
        printf("Cześć tu proces: %d\n",getpid());
        sleep(1);
    }
}
