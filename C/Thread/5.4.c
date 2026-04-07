#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

typedef struct 
{
    int* tab;
    int taille;
} Tableau;

Tableau T1, T2;
int annule = 0; // flag d'annulation

void* generer_tableau(void* arg) 
{
    Tableau* t = (Tableau*) arg;
    t->tab = malloc(t->taille * sizeof(int));
    for(int i=0;i<t->taille;i++){
        t->tab[i] = rand()%100;
    }
    pthread_exit(NULL);
}

void* inclusion(void* arg) 
{
    int found ;
    for(int i=0;i<T1.taille;i++)
    {
        found = 0;
        for(int j=0;j<T2.taille;j++)
        {
            if(T1.tab[i]==T2.tab[j]){
                found = 1;
                break;
            }
        }
        if(!found) 
            break;
    }
    if(annule) {
        printf("Programme annulé par l'utilisateur\n");
    } else {
        printf("T1 %s dans T2\n", found ? "est inclus" : "n'est pas inclus");
    }
    pthread_exit(NULL);
}

void* annulation(void* arg) 
{
    char c;
    c = getchar();
    if(toupper(c)=='A') 
        annule=1;
    pthread_exit(NULL);
}

int main() 
{
    srand(time(NULL));
    T1.taille=5;
    T2.taille=10;

    pthread_t t1_gen, t2_gen, t_incl, t_ann;

    pthread_create(&t1_gen,NULL,generer_tableau,&T1);
    pthread_create(&t2_gen,NULL,generer_tableau,&T2);
    pthread_join(t1_gen,NULL);
    pthread_join(t2_gen,NULL);

    pthread_create(&t_incl,NULL,inclusion,NULL);
    pthread_create(&t_ann,NULL,annulation,NULL);

    pthread_join(t_incl,NULL);
    pthread_join(t_ann,NULL);

    free(T1.tab);
    free(T2.tab);
    return 0;
}