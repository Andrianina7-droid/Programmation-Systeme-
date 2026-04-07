#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if(argc != 2) 
    {
        printf("Usage: %s chemin_cible \n", argv[0]);
        return (1);
    }

    char command[512];
    snprintf(command, sizeof(command), "cp -r . %s", argv[1]);
    system(command);

    return (0);
}