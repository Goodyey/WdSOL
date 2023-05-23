#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main(int argc, char** argv) {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("Błąd funkcji pipe");
        return EXIT_FAILURE;
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Błąd funkcji fork");
        return EXIT_FAILURE;
    }
    
    if (pid == 0) {
        // Proces potomny (serwer)
        close(pipefd[0]); // Zamknięcie strony odczytu
        
        dup2(pipefd[1], STDOUT_FILENO); // Przekierowanie standardowego wyjścia do potoku
        
        int i;
        for (i = 0; i < 10; ++i)
            printf("Serwer: wysyłam linie nr %d\n", i);
        
        fflush(stdout);
        
        close(pipefd[1]); // Zamknięcie strony zapisu
        
        return EXIT_SUCCESS;
    } else {
        // Proces macierzysty (klient)
        close(pipefd[1]); // Zamknięcie strony zapisu
        
        char bufor[BUF_SIZE];
        ssize_t bytesRead;
        
        sleep(1); // Oczekiwanie na inicjalizację potoku przez serwer
        
        while ((bytesRead = read(pipefd[0], bufor, BUF_SIZE)) > 0) {
            printf("Serwer wysłał:\n%.*s", (int)bytesRead, bufor);
        }
        
        if (bytesRead == -1) {
            perror("Błąd funkcji read");
            return EXIT_FAILURE;
        }
        
        close(pipefd[0]); // Zamknięcie strony odczytu
        
        return EXIT_SUCCESS;
    }
}
