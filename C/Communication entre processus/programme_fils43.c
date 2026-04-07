#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int fd = atoi(argv[1]); // 2eme argument : fd 

    char msg[100];
    read(fd, msg, sizeof(msg));

    printf("Message reçu : %s\n", msg);

    return 0;
}