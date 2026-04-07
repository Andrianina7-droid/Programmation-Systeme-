#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define PORT 12348
#define MAX_CLIENTS 10
#define BUFFER 1024

typedef struct {
    int sockfd;
    int pair_sockfd; // socket du client partenaire
} Client;

// Tableau de clients
Client clients[MAX_CLIENTS];
int nb_clients = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Fonction thread pour gérer la communication client
void* client_handler(void* arg) {
    int idx = *(int*)arg;
    char buffer[BUFFER];
    int n;

    while((n = read(clients[idx].sockfd, buffer, BUFFER)) > 0) {
        buffer[n] = '\0';

        // Envoi au client partenaire
        if(clients[idx].pair_sockfd != -1) {
            write(clients[idx].pair_sockfd, buffer, n);
        }
    }

    printf("Client %d déconnecté\n", idx);
    close(clients[idx].sockfd);

    pthread_mutex_lock(&mutex);
    clients[idx].sockfd = -1;
    clients[idx].pair_sockfd = -1;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("bind"); exit(1);
    }

    listen(sockfd, 5);
    printf("Serveur de messagerie en écoute sur port %d...\n", PORT);

    for(int i = 0; i < MAX_CLIENTS; i++){
        clients[i].sockfd = -1;
        clients[i].pair_sockfd = -1;
    }

    while(1) {
        newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
        if(newsockfd < 0){ perror("accept"); continue; }

        pthread_mutex_lock(&mutex);

        int idx = -1;
        for(int i = 0; i < MAX_CLIENTS; i++){
            if(clients[i].sockfd == -1){
                idx = i;
                clients[i].sockfd = newsockfd;
                clients[i].pair_sockfd = -1;
                break;
            }
        }

        if(idx == -1){
            char* msg = "Serveur plein !\n";
            write(newsockfd, msg, strlen(msg));
            close(newsockfd);
            pthread_mutex_unlock(&mutex);
            continue;
        }

        // Relier deux clients par paires
        for(int i = 0; i < MAX_CLIENTS; i++){
            if(i != idx && clients[i].sockfd != -1 && clients[i].pair_sockfd == -1){
                clients[i].pair_sockfd = clients[idx].sockfd;
                clients[idx].pair_sockfd = clients[i].sockfd;
                break;
            }
        }

        pthread_t tid;
        int *p = malloc(sizeof(int));
        *p = idx;
        pthread_create(&tid, NULL, client_handler, p);

        pthread_mutex_unlock(&mutex);
    }

    close(sockfd);
    return 0;
}

