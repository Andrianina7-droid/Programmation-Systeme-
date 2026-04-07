#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>  // Pour srand et rand

#define TAILLE 5

// Fonction du thread
void* generer_tableau(void* arg) 
{
    int* tab = malloc(TAILLE * sizeof(int)); // Allocation dynamique
    if(tab == NULL) 
    {
        perror("malloc");
        pthread_exit(NULL);
    }

    for(int i = 0; i < TAILLE; i++) 
    {
        tab[i] = rand() % 100;  // Valeurs entre 0 et 99
    }

    return (void*)tab; // Retour du tableau
}

int main() 
{
    pthread_t thread;
    srand(time(NULL));  // Initialisation du générateur aléatoire

    // Création du thread
    if(pthread_create(&thread, NULL, generer_tableau, NULL) != 0) 
    {
        perror("pthread_create");
        exit(1);
    }

    // Récupération du résultat
    int* tableau;
    pthread_join(thread, (void**)&tableau); // Le tableau est retourné ici

    // Affichage du tableau
    printf("Tableau généré par le thread : ");
    for(int i = 0; i < TAILLE; i++) 
    {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    free(tableau); // Libération mémoire
    return 0;
}