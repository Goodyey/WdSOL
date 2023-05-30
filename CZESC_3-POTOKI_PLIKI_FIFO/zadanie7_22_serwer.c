#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_FILE "fifo_file"

int main(int argc, char** argv) {
    mkfifo(FIFO_FILE, 0666); // Tworzenie potoku nazwanego

    int fd = open(FIFO_FILE, O_WRONLY); // Otwarcie potoku nazwanego w trybie zapisu

    int i;
    for (i = 0; i < 10; ++i)
        printf("Serwer: wysyłam linie nr %d\n", i);

    fflush(stdout);

    close(fd); // Zamknięcie potoku

    return EXIT_SUCCESS;
}
