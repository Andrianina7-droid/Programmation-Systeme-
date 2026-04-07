#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5000
#define MAXLINE 1024
#define MAX_PRODUCTS 100

typedef struct {
    char name[50];
    float price;
} Product;

int main() {
    Product products[MAX_PRODUCTS];
    int n_products = 0;

    // Charger la base de produits
    FILE *f = fopen("produits.txt", "r");
    if (!f) { perror("produits.txt"); return 1; }
    while (fscanf(f, "%s %f", products[n_products].name, &products[n_products].price) != EOF) {
        n_products++;
    }
    fclose(f);

    // Création du serveur TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    printf("Serveur lancé sur le port %d\n", PORT);

    while (1) {
        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
        printf("Connexion acceptée\n");

        char buffer[MAXLINE];
        send(connfd, "Nom du produit : ", 17, 0);
        int n = read(connfd, buffer, MAXLINE); buffer[n-1]='\0';
        char product_name[50]; 
        strcpy(product_name, buffer);

        send(connfd, "Quantité : ", 11, 0);
        n = read(connfd, buffer, MAXLINE)
        ; buffer[n-1]='\0';
        int qty = atoi(buffer);

        send(connfd, "Votre nom : ", 12, 0);
        n = read(connfd, buffer, MAXLINE); 
        buffer[n-1]='\0';
        char client_name[50]; 
        strcpy(client_name, buffer);

        float total = -1;
        for (int i=0; i<n_products; i++) {
            if (strcmp(products[i].name, product_name)==0) {
                total = products[i].price * qty;
                break;
            }
        }

        if (total >= 0) {
            sprintf(buffer, "Prix total = %.2f\n", total);
            send(connfd, buffer, strlen(buffer), 0);

            char filename[100];
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            strftime(filename, 100, "commande_%Y%m%d_%H%M%S.txt", tm_info);
            FILE *fcmd = fopen(filename, "w");
            fprintf(fcmd, "Client: %s\nProduit: %s\nQuantité: %d\nTotal: %.2f\n",
                    client_name, product_name, qty, total);
            fclose(fcmd);
        } else {
            send(connfd, "Produit non trouvé\n", 19, 0);
        }
        close(connfd);
    }
    return 0;
}