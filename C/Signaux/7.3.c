#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

pid_t pids[N];

void child_handler(int sig) {
    printf("Fils %d tué !\n", getpid());
    exit(0);
}

int main() {
    for(int i=0;i<N;i++) {
        pids[i] = fork();
        if(pids[i]==0) {
            signal(SIGTERM, child_handler);
            while(1) {}
        }
    }

    int choix, fils;
    while(1) {
        printf("Menu : 1=endormir, 2=réveiller, 3=terminer, 4=quit\nChoix : ");
        scanf("%d", &choix);
        if(choix==4) break;
        printf("Numéro du fils (0-%d) : ", N-1);
        scanf("%d", &fils);

        if(choix==1) 
            kill(pids[fils], SIGSTOP);
        else if(choix==2) 
            kill(pids[fils], SIGCONT);
        else if(choix==3) 
            kill(pids[fils], SIGTERM);
    }
}