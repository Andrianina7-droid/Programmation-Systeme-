#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int top = 0; // Index de la prochaine position libre

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full;   // nombre d'éléments disponibles
sem_t empty;  // nombre de places libres

void* producer(void* arg) 
{
    int id = *(int*)arg;
    while(1) {
        int item = rand() % 256; // produire un octet aléatoire
        sem_wait(&empty);        // attendre place libre
        pthread_mutex_lock(&mutex); 
        buffer[top++] = item;     // placer l'octet
        printf("Producteur %d : produit %d, top=%d\n", id, item, top);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);          // signaler élément disponible
        sleep(rand()%3 + 1);
    }
    return NULL;
}

void* consumer(void* arg) 
{
    int id = *(int*)arg;
    while(1) {
        sem_wait(&full);          // attendre qu'un élément soit disponible
        pthread_mutex_lock(&mutex);
        int item = buffer[--top]; // consommer l'élément
        printf("Consommateur %d : consomme %d, top=%d\n", id, item, top);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);         // signaler place libre
        sleep(rand()%3 + 1);
    }
    return NULL;
}

int main() 
{
    srand(time(NULL));
    int N = 2, M = 2; // producteurs et consommateurs
    pthread_t producers[N], consumers[M];
    int ids[N>M?N:M];
    
    sem_init(&full, 0, 0);             // aucun élément initial
    sem_init(&empty, 0, BUFFER_SIZE);  // tampon vide

    for(int i=0;i<N;i++)
    {   
        ids[i]=i; 
        pthread_create(&producers[i], NULL, producer, &ids[i]); 
    }
    for(int i=0;i<M;i++) 
    { 
        ids[i]=i; 
        pthread_create(&consumers[i], NULL, consumer, &ids[i]); 
    }

    for(int i=0;i<N;i++) 
    {
        pthread_join(producers[i], NULL);
    }
    for(int i=0;i<M;i++) 
    {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}