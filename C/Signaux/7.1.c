#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if(pid == 0) {
        // Fils : calcul sans fin
        int x = 0;
        while(1) {
            x += 1; // calcul simple
        }
    } else {
        // Père : menu de contrôle
        char choix;
        while(1) 
        {
            printf("Menu : s = stop, r = resume, q = quit\n");
            scanf(" %c", &choix); // espace avant %c pour consommer \n
            if(choix == 's') {
                kill(pid, SIGSTOP); // endort le fils
            } 
            else if(choix == 'r') {
                kill(pid, SIGCONT); // réveille le fils
            } 
            else if(choix == 'q') {
                kill(pid, SIGKILL); // tue le fils
                break;
            }
        }
    }

    return 0;
}