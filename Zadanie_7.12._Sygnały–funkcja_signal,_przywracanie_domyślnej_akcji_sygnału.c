#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//zmodyfikowana wersja programu - obsługa sygnałów SIGINT i SIGQUIT
//po naciśnięciu CTRL+C wyświetla cykliczne 3 napisy, po naciśnięciu CTRL+\ przywraca standardową obsługę SIGINT

char napisy[3][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\
n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n",
"Auć - to bolało!\n"};
int nr_napisu=0;

void obsluga_sig_int(int sig, siginfo_t* info, void* context) {
    if (sig == SIGINT) {
        printf(napisy[nr_napisu], getpid(), sig);
        nr_napisu = (nr_napisu + 1) % 3;
    } else if (sig == SIGQUIT) {
        printf("Przywracam standardową obsługę sygnału SIGINT\n");
        signal(SIGINT, SIG_DFL);
    }
}

int main(int argc, char** argv) {
    struct sigaction act;
    act.sa_sigaction = obsluga_sig_int;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &act, NULL);
    signal(SIGQUIT, SIG_IGN);

    while (true) {
        printf("Cześć tu proces: %d\n", getpid());
        sleep(1);
    }
}
