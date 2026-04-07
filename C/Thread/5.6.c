#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex pour protéger le tableau

void* calcul_moyenne(void* arg) 
{
    for (int i = 1; i < N-1; i++) {
        pthread_mutex_lock(&mutex); // Début section critique
        tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3;
        pthread_mutex_unlock(&mutex); // Fin section critique
        usleep((rand()%3 + 1) * 1000000); // pause entre 1 et 3 secondes
    }
    return NULL;
}

void* affichage(void* arg) 
{
    while(1) {
        pthread_mutex_lock(&mutex);
        for(int i=0; i<N; i++)
            printf("%.2f ", tableau[i]);
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(4); // Affiche toutes les 4 secondes
    }
    return NULL;
}

int main() 
{
    srand(time(NULL));
    for(int i=0; i<N; i++)
        tableau[i] = rand()%101; // Valeurs aléatoires 0-100

    tableau[0] = 0; tableau[N-1] = 0; // extrémités fixées

    pthread_t t1, t2;
    pthread_create(&t1, NULL, calcul_moyenne, NULL);
    pthread_create(&t2, NULL, affichage, NULL);

    pthread_join(t1, NULL); // Attend que le thread calcul se termine
    pthread_cancel(t2); // Stoppe l'affichage
    pthread_join(t2, NULL);

    return 0;
}