#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12348
#define BUFFER 1024

int sockfd;

void* receive_handler(void* arg){
    char buffer[BUFFER];
    int n;
    while((n = read(sockfd, buffer, BUFFER)) > 0){
        buffer[n] = '\0';
        printf("L'autre client dit : %s\n", buffer);
    }
    return NULL;
}

int main() {
    struct sockaddr_in serv_addr;
    char buffer[BUFFER];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){ perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("connect"); exit(1);
    }

    pthread_t tid;
    pthread_create(&tid, NULL, receive_handler, NULL);

    while(1){
        printf("Saisissez votre message : ");
        fgets(buffer, BUFFER, stdin);
        write(sockfd, buffer, strlen(buffer));
    }

    close(sockfd);
    return 0;
}