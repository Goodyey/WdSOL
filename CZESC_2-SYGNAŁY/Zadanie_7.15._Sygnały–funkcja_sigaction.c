#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char napisy[3][80] = {"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n",
"Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n",
"Auć - to bolało!\n"};
int nr_napisu = 0;
int licznik_ctrl_c = 0;

// Funkcja obsługująca sygnał SIGINT
void obsluga_sig_int(int sig) {
    printf("Obsługa sygnału SIGINT...\n");
    sleep(2);  // Obsługa sygnału trwa 2 sekundy
    printf("Zakończono obsługę sygnału SIGINT.\n");
    if (sig == SIGINT) {
        licznik_ctrl_c++;
        if (licznik_ctrl_c == 4) {
            printf("Dobrze! Dobrze! Już kończę.\n");
            exit(0);
        }
        printf(napisy[nr_napisu], getpid(), sig);
        nr_napisu = ((nr_napisu + 1) % 3);
    }
}

int main(int argc, char **argv) {
    struct sigaction act;

    // Blokowanie sygnałów SIGINT i SIGQUIT
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    sigaddset(&act.sa_mask, SIGQUIT);

    act.sa_flags = 0;
    act.sa_handler = obsluga_sig_int;

    // Instalowanie obsługi sygnału SIGINT
    if (sigaction(SIGINT, &act, NULL) < 0) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Ustawienie domyślnej obsługi sygnału SIGQUIT
    signal(SIGQUIT, SIG_DFL);

    sigset_t mask;

    // Inicjalizacja pustego zbioru sygnałów
    sigemptyset(&mask);

    // Dodanie sygnałów SIGINT i SIGQUIT do zbioru
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    // Zablokowanie sygnałów SIGINT i SIGQUIT przez 15 sekund
    sigprocmask(SIG_BLOCK, &mask, NULL);
    printf("Obsługa sygnału SIGINT zablokowana przez 15 sekund.\n");

    sleep(15);  // Obsługa sygnałów zablokowana przez 15 sekund

    int sig_num;
    sigset_t pending;

    // Sprawdzenie, czy sygnał SIGINT został odebrany podczas blokady
    sigpending(&pending);
    if (sigismember(&pending, SIGINT)) {
        printf("Sygnał SIGINT został odebrany podczas blokady.\n");
    }

    // Sprawdzenie, czy sygnał SIGQUIT został odebrany podczas blokady
    if (sigismember(&pending, SIGQUIT)) {
        printf("Sygnał SIGQUIT został odebrany podczas blokady.\n");
    }

    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    printf("Obsługa sygnałów odblokowana.\n");

    while (1) {
        printf("Cześć tu proces: %d\n", getpid());
        sleep(1);
    }

    return EXIT_SUCCESS;
}
