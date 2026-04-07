#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if(pid == 0) 
    {
        char r[10];
        sprintf(r, "%d", fd[0]); // passer fd en string

        execl("./fils", "fils", r, NULL);
    }
    else {
        char msg[] = "Hellooooo depuis le père";

        write(fd[1], msg, sizeof(msg));
    }

    return 0;
}