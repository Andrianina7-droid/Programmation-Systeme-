#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>

#define PORT 12347
#define BUF_SIZE 1024

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){ perror("socket"); return 1; }

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){ perror("bind"); return 1; }
    listen(sockfd,5);
    printf("Serveur en écoute sur le port %d\n", PORT);

    int newsock = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
    if(newsock<0){ perror("accept"); return 1; }

    // Récupération de l'adresse IP du client
    char ip_client[50];
    strcpy(ip_client, inet_ntoa(cli_addr.sin_addr));

    // Création nom fichier avec IP et date
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char filename[100];
    sprintf(filename,"/home/save/%s_%04d_%02d_%02d.txt", ip_client,
            tm_info->tm_year+1900, tm_info->tm_mon+1, tm_info->tm_mday);

    FILE *fp = fopen(filename,"wb");
    if(!fp){ perror("fopen"); return 1; }

    // Réception du fichier
    char buf[BUF_SIZE];
    ssize_t n;
    while((n=read(newsock,buf,BUF_SIZE))>0){
        fwrite(buf,1,n,fp);
    }

    fclose(fp);
    close(newsock);
    close(sockfd);
    printf("Fichier reçu et sauvegardé dans %s\n", filename);
    return 0;
}