#include <stdio.h>
#include <pthread.h>

void* afficher_tableau(void* arg) 
{
    int* tab = (int*)arg; // Conversion du pointeur générique
    int n = 5; // Taille du tableau

    printf("Affichage du tableau : ");
    for(int i = 0; i < n; i++) 
    {
        printf("| %d ", tab[i]);
    }
    printf("|\n");

    return NULL;
}

int main() 
{
    pthread_t thread1; // Déclaration du thread
    int tableau[5] = {1, 2, 3, 4, 5};

    // Création du thread
    pthread_create(&thread1, NULL, afficher_tableau, (void*)tableau);

    // Attendre la fin du thread
    pthread_join(thread1, NULL);

    printf("Thread principal terminé\n");
    return 0;
}