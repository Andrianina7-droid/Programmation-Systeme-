#include <stdio.h>
#include <unistd.h>

int num = 0;

int main() 
{
    for (int i = 1; i <= 5; i++) 
    {
        pid_t pid = fork();

        if (pid == 0) 
        {
            num = i;
            printf("Je suis le fils %d\n", num);
            break;
        }
    }
    return 0;
}