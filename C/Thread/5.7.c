#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double u = 1;
int compteur = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 

void* thread1(void* arg) 
{
    while(compteur < 10) {
        pthread_mutex_lock(&mutex);
        compteur++;
        u = (u - 1)*(u - 1)/4;
        printf("T1 -> u = %.2f, compteur = %d\n", u, compteur);
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5 + 1);
    }
    return NULL;
}

void* thread2(void* arg) 
{
    while(compteur < 10) {
        pthread_mutex_lock(&mutex);
        compteur++;
        u = (u - 2)*(u - 2)/6;
        printf("T2 -> u = %.2f, compteur = %d\n", u, compteur);
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5 + 1);
    }
    return NULL;
}

int main() 
{
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}