#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork(); 

    if(pid == 0) 
    { 
        // Redirection : stdin du fils = lecture du pipe
        close(fd[1]);       // On ferme l'écriture dans le fils
        dup2(fd[0], STDIN_FILENO); // stdin du fils reçoit les données du pipe
        close(fd[0]);       // fd[0] n'est plus nécessaire après dup2

        // Lecture du mot depuis stdin (qui vient du père)
        char word[100];
        scanf("%s", word);

        // Affiche le mot reçu
        printf("Fils : mot reçu = %s\n", word);
        exit(0);
    }
    else 
    {
        close(fd[0]); // On ferme la lecture dans le père

        char msg[100];
        printf("Père : entrez un mot à envoyer au fils : ");
        scanf("%s", msg);

        // Écriture dans le pipe
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]); // Fermeture de l'écriture après envoi

        wait(NULL); // On attend que le fils termine
    }

    return 0;
}