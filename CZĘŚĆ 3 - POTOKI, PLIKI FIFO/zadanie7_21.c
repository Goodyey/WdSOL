#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_FILE "fifo_file"

#define BUF_SIZE 2048

int main(int argc, char** argv) {
    mkfifo(FIFO_FILE, 0666); // Tworzenie potoku nazwanego
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Błąd funkcji fork");
        return EXIT_FAILURE;
    }
    
    if (pid == 0) {
        // Proces potomny (serwer)
        int fd = open(FIFO_FILE, O_WRONLY); // Otwarcie potoku nazwanego w trybie zapisu
        
        int i;
        for (i = 0; i < 10; ++i)
            printf("Serwer: wysyłam linie nr %d\n", i);
        
        fflush(stdout);
        
        close(fd); // Zamknięcie potoku
        
        return EXIT_SUCCESS;
    } else {
        // Proces macierzysty (klient)
        int fd = open(FIFO_FILE, O_RDONLY); // Otwarcie potoku nazwanego w trybie odczytu
        
        char bufor[BUF_SIZE];
        ssize_t bytesRead;
        
        sleep(1); // Oczekiwanie na inicjalizację potoku przez serwer
        
        while ((bytesRead = read(fd, bufor, BUF_SIZE)) > 0) {
            printf("Serwer wysłał:\n%.*s", (int)bytesRead, bufor);
        }
        
        if (bytesRead == -1) {
            perror("Błąd funkcji read");
            return EXIT_FAILURE;
        }
        
        close(fd); // Zamknięcie potoku
        
        return EXIT_SUCCESS;
    }
}
