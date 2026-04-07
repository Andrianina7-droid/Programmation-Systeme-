#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compt = 0;              // Compteur global
int limite;                  // Valeur limite
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread qui incrémente le compteur
void* incrementer(void* arg) 
{
    while(1) {
        pthread_mutex_lock(&mutex);   // Début section critique
        if(compt >= limite) 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        compt++;
        pthread_mutex_unlock(&mutex); // Fin section critique

        sleep(rand()%5 + 1);          // Attend 1 à 5 secondes
    }
    pthread_exit(NULL);
}

// Thread qui affiche le compteur
void* afficher(void* arg) 
{
    while(1) {
        pthread_mutex_lock(&mutex);
        if(compt >= limite) 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Compteur = %d\n", compt);
        pthread_mutex_unlock(&mutex);

        sleep(2);                      // Affiche toutes les 2 secondes
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) 
{
    if(argc != 2) {
        printf("Usage: %s [valeur_limite]\n", argv[0]);
        return 1;
    }
    limite = atoi(argv[1]);
    srand(time(NULL));

    pthread_t t_inc, t_aff;

    pthread_create(&t_inc, NULL, incrementer, NULL);
    pthread_create(&t_aff, NULL, afficher, NULL);

    pthread_join(t_inc, NULL);
    pthread_join(t_aff, NULL);

    return 0;
}