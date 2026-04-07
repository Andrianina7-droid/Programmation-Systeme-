#include <stdio.h>  
#include <unistd.h>

int main()
{
    pid_t pid;
    
    for(int i = 0 ; i < 5 ; i++)
    {
        pid = fork();

        if(pid == 0)
        {
            printf("Je suis le fils %d\n", i+1);
            break; 
        }       
    }

    return 0;
}