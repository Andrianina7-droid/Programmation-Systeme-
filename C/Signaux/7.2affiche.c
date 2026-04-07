#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    FILE *f = fopen("/tmp/entier.txt", "r");
    int n;
    fscanf(f, "%d", &n);
    fclose(f);
    printf("Entier reçu : %d\n", n);
}

int main() {
    signal(SIGUSR1, handler);
    printf("PID = %d, en attente du signal...\n", getpid());
    while(1) pause(); // attendre signal
}