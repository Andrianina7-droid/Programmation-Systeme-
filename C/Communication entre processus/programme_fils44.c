#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
    // récupérer la variable d'environnement
    char *fd_str = getenv("FD");

    // convertir en entier
    int fd = atoi(fd_str);

    char msg[100];
    read(fd, msg, sizeof(msg));

    printf("Message reçu : %s\n", msg);

    return 0;
}