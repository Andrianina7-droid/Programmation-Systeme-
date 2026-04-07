/* Exercices 2.1 */
#include <stdio.h>  
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main() 
{
    pid_t pid = fork();

    if(pid == -1)
    {
        perror("Erreur de creation du processus ");
        exit(1);
    }
    else if (pid == 0) 
    {
        printf("Je suis le fils \n");
    } 
    else 
    {
        printf("Je suis le père \n");
    }

    return (0);
}