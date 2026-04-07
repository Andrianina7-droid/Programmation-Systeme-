#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    pid_t pid_1, pid_2;   
    time_t debut, fin;    // Variables pour mesurer le temps total

    debut = time(NULL);   // Début du programme

    // Création du premier fils
    pid_1 = fork();

    if(pid_1 == 0)
    {
        // Code exécuté uniquement par le FILS 1
        srand(getpid()); // important : seed différent pour chaque fils
        int t = rand() % 10 + 1; // Temps aléatoire entre 1 et 10
        printf("Fils 1 dort pendant %d secondes\n", t);
        sleep(t); // Le fils dort 
        printf("Fils 1 terminé\n");
        exit(0); //empêche ce fils de continuer le programme
    }
    else
    {
        // Code exécuté uniquement par le PÈRE

        // Création du deuxième fils
        pid_2 = fork();

        if(pid_2 == 0)
        {
            // Code exécuté uniquement par le FILS 2
            srand(getpid()); // Seed différent
            int t = rand() % 10 + 1;
            printf("Fils 2 dort pendant %d secondes\n", t);
            sleep(t);
            printf("Fils 2 terminé\n");
            exit(0); 
        }
    }

    // Code exécuté uniquement par le PÈRE (après création des fils)

    wait(NULL); // Le père attend la fin d'un fils
    wait(NULL); // Le père attend le deuxième fils

    fin = time(NULL); // Fin du programme

    printf("Durée totale d'exécution : %ld secondes\n", fin - debut);

    return 0;
}