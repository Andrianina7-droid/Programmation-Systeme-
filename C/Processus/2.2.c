#include <stdio.h>
#include <unistd.h>

int main() 
{
    pid_t pid1 = fork();

    if (pid1 == 0) 
    {
        printf("Je suis le fils 1 \n");
    } 
    else 
    {
        pid_t pid2 = fork();
        if (pid2 == 0) 
        {
            printf("Je suis le fils 2 \n");
        } 
        else {
            printf("Je suis le père \n");
        }
    }
    return (0);
}
