#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12349
#define MAX_CLIENTS 20
#define BUFFER 1024

int clients[MAX_CLIENTS];
int nb_clients = 0;
pthread_mutex_t mutex_clients = PTHREAD_MUTEX_INITIALIZER; // protège le tableau clients
pthread_mutex_t mutex_send = PTHREAD_MUTEX_INITIALIZER;    // protège l'envoi d'un message

// envoyer un message à tous les clients sauf celui qui envoie
void broadcast(char* msg, int sender_fd) {
    pthread_mutex_lock(&mutex_send);
    for(int i = 0; i < nb_clients; i++){
        if(clients[i] != sender_fd){
            write(clients[i], msg, strlen(msg));
        }
    }
    pthread_mutex_unlock(&mutex_send);
}

// thread pour gérer chaque client
void* client_handler(void* arg){
    int sockfd = *(int*)arg;
    char buffer[BUFFER];
    int n;

    while((n = read(sockfd, buffer, BUFFER-1)) > 0){
        buffer[n] = '\0';
        char msg[BUFFER+50];
        snprintf(msg, sizeof(msg), "Client %d dit : %s", sockfd, buffer);
        broadcast(msg, sockfd);
    }

    printf("Client %d déconnecté\n", sockfd);

    // retirer le client du tableau
    pthread_mutex_lock(&mutex_clients);
    for(int i = 0; i < nb_clients; i++){
        if(clients[i] == sockfd){
            for(int j=i;j<nb_clients-1;j++)
                clients[j]=clients[j+1];
            nb_clients--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex_clients);

    close(sockfd);
    return NULL;
}

int main(){
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){ perror("bind"); exit(1); }
    listen(sockfd, 5);
    printf("Serveur forum de chat en écoute sur port %d...\n", PORT);

    while(1){
        newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
        if(newsockfd < 0){ perror("accept"); continue; }

        pthread_mutex_lock(&mutex_clients);
        if(nb_clients < MAX_CLIENTS){
            clients[nb_clients++] = newsockfd;
            pthread_t tid;
            int *p = malloc(sizeof(int));
            *p = newsockfd;
            pthread_create(&tid, NULL, client_handler, p);
        } else {
            char* msg = "Serveur plein !\n";
            write(newsockfd, msg, strlen(msg));
            close(newsockfd);
        }
        pthread_mutex_unlock(&mutex_clients);
    }

    close(sockfd);
    return 0;
}