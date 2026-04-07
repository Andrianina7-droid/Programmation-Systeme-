#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if(pid == 0) 
    {
        // convertir fd[0] en chaîne
        char r[10];
        sprintf(r, "%d", fd[0]);

        // mettre dans variable d'environnement
        setenv("FD", r, 1);

        // lancer le programme fils
        execl("./fils", "fils", NULL);
    }
    else
    {
        char msg[] = "Hellooooo depuis le père";

        write(fd[1], msg, sizeof(msg));
    }

    return 0;
}