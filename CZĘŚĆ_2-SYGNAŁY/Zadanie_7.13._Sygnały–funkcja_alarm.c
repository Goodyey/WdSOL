#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//zmodyfikowana wersja programu - obsługa sygnałów SIGINT, SIGQUIT i SIGALRM
//po naciśnięciu CTRL+C wyświetla cykliczne 3 napisy, po naciśnięciu CTRL+\ przywraca standardową obsługę SIGINT
//po 15 sekundach od uruchomienia programu następuje przywrócenie standardowej obsługi SIGINT

char napisy[3][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n", "Auć - to bolało!\n"};
int nr_napisu=0;

void obsluga_sig_int(int sig, siginfo_t* info, void* context) {
    if (sig == SIGINT) {
        printf(napisy[nr_napisu], getpid(), sig);
        nr_napisu = (nr_napisu + 1) % 3;
    } else if (sig == SIGQUIT) {
        printf("Przywracam standardową obsługę sygnału SIGINT\n");
        signal(SIGINT, SIG_DFL);
    } else if (sig == SIGALRM) {
        printf("Ding! Ding! Ding! - Przywracam domyślną obsługę CTRL+C\n");
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
    signal(SIGALRM, obsluga_sig_int);
    alarm(15);

    while (true) {
        printf("Cześć tu proces: %d\n", getpid());
        sleep(1);
    }
}
