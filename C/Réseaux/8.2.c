#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12346
#define MAX 100

typedef struct {
    char ip[50];
    char nom[50];
} ClientAutorise;

// Charger les IP autorisées
int chargerClients(ClientAutorise tab[], const char* fichier) {
    FILE *fp = fopen(fichier,"r");
    if(!fp){ perror("fopen"); return 0; }
    int n=0;
    while(fscanf(fp,"%s %s", tab[n].ip, tab[n].nom)==2) n++;
    fclose(fp);
    return n;
}

// Vérifier si IP est autorisée
ClientAutorise* verifierIP(ClientAutorise tab[], int n, char* ip) {
    for(int i=0;i<n;i++)
        if(strcmp(tab[i].ip,ip)==0) return &tab[i];
    return NULL;
}

int main() {
    ClientAutorise clients[MAX];
    int nClients = chargerClients(clients,"add_autoris.txt");
    if(nClients==0){ printf("Aucun client autorisé.\n"); return 1; }

    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){ perror("bind"); exit(1);}
    listen(sockfd,5);
    printf("Serveur en écoute sur port %d...\n", PORT);

    newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
    if(newsockfd<0){ perror("accept"); exit(1); }

    char ip_client[50];
    strcpy(ip_client, inet_ntoa(cli_addr.sin_addr));
    ClientAutorise* c = verifierIP(clients,nClients,ip_client);

    if(c){
        char msg[100];
        sprintf(msg,"Bienvenue %s !\n", c->nom);
        write(newsockfd,msg,strlen(msg));
        printf("Client %s connecté et autorisé.\n", ip_client);
    } else {
        char* msg="Vous n'êtes pas autorisé !\n";
        write(newsockfd,msg,strlen(msg));
        printf("Client %s refusé.\n", ip_client);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}