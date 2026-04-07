#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    int n;
    printf("Entrez un entier : ");
    scanf("%d", &n);

    FILE *f = fopen("/tmp/entier.txt", "w");
    fprintf(f, "%d\n", n);
    fclose(f);

    pid_t pid_affiche;
    printf("PID du programme affiche.c : ");
    scanf("%d", &pid_affiche);

    kill(pid_affiche, SIGUSR1); // envoyer signal
    return 0;
}