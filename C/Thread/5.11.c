#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 15

int data[SIZE];     // base de données (tableau)
int read_count = 0; // nombre de lecteurs actifs

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // protège read_count
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;   // protège la base


void* reader(void* arg)
{
    int id = *(int*)arg;

    while(1)
    {
        // on protège read_count
        pthread_mutex_lock(&mutex);
        read_count++;

        if(read_count == 1)
            pthread_mutex_lock(&wrt); // premier lecteur bloque écrivains

        pthread_mutex_unlock(&mutex);

        // lecture (pas critique)
        int i = rand() % SIZE;
        printf("Lecteur %d lit data[%d] = %d\n", id, i, data[i]);

        sleep(rand()%3 + 1);

        // fin lecture
        pthread_mutex_lock(&mutex);
        read_count--;

        if(read_count == 0)
            pthread_mutex_unlock(&wrt); // dernier lecteur libère écrivains

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


void* writer(void* arg)
{
    int id = *(int*)arg;

    while(1)
    {
        pthread_mutex_lock(&wrt); // accès exclusif

        int i = rand() % SIZE;
        data[i] = rand() % 100;

        printf("Écrivain %d écrit data[%d] = %d\n", id, i, data[i]);

        pthread_mutex_unlock(&wrt);

        sleep(rand()%5 + 1);
    }

    return NULL;
}


int main()
{
    srand(time(NULL));

    int N = 3; // lecteurs
    int M = 2; // écrivains

    pthread_t readers[N], writers[M];
    int ids[N > M ? N : M];

    // création lecteurs
    for(int i=0;i<N;i++)
    {
        ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    // création écrivains
    for(int i=0;i<M;i++)
    {
        ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // attente
    for(int i=0;i<N;i++)
        pthread_join(readers[i], NULL);

    for(int i=0;i<M;i++)
        pthread_join(writers[i], NULL);

    return 0;
}