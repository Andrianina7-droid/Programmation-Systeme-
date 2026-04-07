#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>

#define PORT 12347
#define BUFFER 4096

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER];

    // Créer socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connecter le client
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("connect"); exit(1);
    }

    // Créer archive tar.gz du répertoire client
    system("tar zcvf /tmp/rep.tgz /chemin/vers/le/repertoire/client");

    // Ouvrir l'archive
    FILE *f = fopen("/tmp/rep.tgz", "rb");
    if(!f){ perror("fopen"); exit(1); }

    // Envoyer l'archive
    int n;
    while((n = fread(buffer, 1, BUFFER, f)) > 0){
        write(sockfd, buffer, n);
    }

    fclose(f);
    close(sockfd);
    printf("Archive envoyée au serveur !\n");
    return 0;
}