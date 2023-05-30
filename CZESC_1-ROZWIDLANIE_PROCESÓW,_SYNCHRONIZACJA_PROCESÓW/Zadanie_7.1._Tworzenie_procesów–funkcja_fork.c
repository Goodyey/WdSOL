#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    pid_t pid_potomka;
    char *komunikat;
    int powtorzen;
    printf("Na razie działa jeden proces\n");
    pid_potomka = fork();
    switch (pid_potomka) {
        case -1:
            printf("rozwidlenie procesu nie powiodło się\n");
            exit(1);
        case 0:
            komunikat = "Jestem potomkiem";
            powtorzen = 5;
            break;
        default:
            komunikat = "Jestem rodzicem";
            powtorzen = 5;
            break;
    }
    for (; powtorzen > 0; powtorzen--) {
        puts(komunikat);
        sleep(1);
    }
}