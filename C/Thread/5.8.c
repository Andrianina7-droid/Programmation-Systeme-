#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t sem1, sem2; // 2 sémaphores pour synchronisation

void* thread1(void* arg) 
{
    for(int i=0; i<10; i++) 
    {
        printf("T1 : traitement iteration %d\n", i+1);
        sleep(2); // traitement de 2 sec
        sem_post(&sem1); // signal que T1 a fini
        sem_wait(&sem2); // attend T2
    }
    return NULL;
}

void* thread2(void* arg) 
{
    for(int i=0; i<10; i++) {
        sem_wait(&sem1); // attend T1
        int t = rand()%6 + 4; // traitement aléatoire 4-9 sec
        printf("T2 : traitement iteration %d pour %d sec\n", i+1, t);
        sleep(t);
        sem_post(&sem2); // signal que T2 a fini
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem1, 0, 0); // initialisation des sémaphores à 0
    sem_init(&sem2, 0, 0);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}