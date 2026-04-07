#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>

#define PORT 12347
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Usage: %s <fichier_local>\n", argv[0]);
        return 1;
    }

    // Création du socket client
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){ perror("socket"); return 1; }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // serveur local pour test

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
        perror("connect"); return 1;
    }

    // Ouverture du fichier local
    FILE *fp = fopen(argv[1],"rb");
    if(!fp){ perror("fopen"); return 1; }

    // Envoi du fichier
    char buf[BUF_SIZE];
    size_t n;
    while((n=fread(buf,1,BUF_SIZE,fp))>0){
        write(sockfd, buf, n);
    }
    fclose(fp);
    close(sockfd);

    printf("Fichier envoyé avec succès.\n");
    return 0;
}