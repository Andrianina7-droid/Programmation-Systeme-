#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct 
{
    int* tab;
    int taille;
    int x; // valeur à chercher
} TypeTableau;

void* generer_tableau(void* arg) 
{
    TypeTableau* t = (TypeTableau*) arg;
    t->tab = malloc(t->taille * sizeof(int));
    if(t->tab == NULL) 
    { 
        perror("malloc"); 
        pthread_exit(NULL); 
    }

    for(int i = 0; i < t->taille; i++) 
    {
        t->tab[i] = rand() % 100;
    }
    pthread_exit(NULL);
}

void* chercher_x(void* arg) 
{
    TypeTableau* t = (TypeTableau*) arg;
    int found = 0;
    for(int i = 0; i < t->taille; i++) 
    {
        if(t->tab[i] == t->x) 
        {
            found = 1;
            break;
        }
    }
    printf("Résultat : x %s dans le tableau\n", found ? "est" : "n'est pas");
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    TypeTableau t;
    printf("Saisir la taille du tableau : ");
    scanf("%d", &t.taille);

    printf("Saisir la valeur à chercher x : ");
    scanf("%d", &t.x);

    pthread_t thread_gen, thread_cherche;

    // Création du thread de génération
    pthread_create(&thread_gen, NULL, generer_tableau, &t);
    pthread_join(thread_gen, NULL); // attendre que le tableau soit généré

    // Création du thread de recherche
    pthread_create(&thread_cherche, NULL, chercher_x, &t);
    pthread_join(thread_cherche, NULL);

    free(t.tab);
    return 0;
}