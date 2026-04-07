#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT 12347
#define BUFFER 4096

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    char buffer[BUFFER];

    // Créer le socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("bind"); exit(1);
    }

    // Listen
    listen(sockfd, 5);
    printf("Serveur en écoute sur port %d...\n", PORT);

    // Accept
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if(newsockfd < 0){ perror("accept"); exit(1); }

    printf("Client connecté : %s\n", inet_ntoa(cli_addr.sin_addr));

    // Créer un fichier temporaire pour l'archive
    FILE *f = fopen("/tmp/rep.tgz", "wb");
    if(!f){ perror("fopen"); exit(1); }

    // Lire les données envoyées par le client
    int n;
    while((n = read(newsockfd, buffer, BUFFER)) > 0){
        fwrite(buffer, 1, n, f);
    }
    fclose(f);
    printf("Archive reçue !\n");

    // Décompresser l'archive et supprimer le fichier
    system("cd /home/save/ ; tar zxvf /tmp/rep.tgz ; rm /tmp/rep.tgz");
    printf("Archive décompressée sur le serveur.\n");

    close(newsockfd);
    close(sockfd);
    return 0;
}