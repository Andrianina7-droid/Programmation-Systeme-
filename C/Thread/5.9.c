#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int octet;
int ready = 0; // indique si l'octet est prêt

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* emetteur(void* arg)
{
    for(int i=0;i<10;i++){
        sleep(rand()%3 + 1); // temps aléatoire 1-3 sec
        pthread_mutex_lock(&mutex);
        while(ready) 
            pthread_cond_wait(&cond,&mutex); // attend que octet lu
        octet = rand()%256;
        ready = 1;
        printf("Émetteur : octet %d envoyé\n", octet);
        pthread_cond_signal(&cond); // réveille le recepteur
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* recepteur(void* arg)
{
    for(int i=0;i<10;i++){
        pthread_mutex_lock(&mutex);
        while(!ready) 
            pthread_cond_wait(&cond,&mutex); // attend octet
        printf("Récepteur : octet %d reçu\n", octet);
        ready = 0;
        pthread_cond_signal(&cond); // réveille l'emetteur
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    pthread_t t1,t2;

    pthread_create(&t1,NULL,emetteur,NULL);
    pthread_create(&t2,NULL,recepteur,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}