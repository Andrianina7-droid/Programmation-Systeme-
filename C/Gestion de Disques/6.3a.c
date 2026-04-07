#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int n;
    printf("Nombre d'entiers à saisir : ");
    scanf("%d", &n);

    int *tab = malloc(n * sizeof(int));
    if(!tab) 
    { 
        perror("malloc"); 
        return 1; 
    }

    for(int i=0;i<n;i++) {
        printf("Entier %d : ", i);
        scanf("%d", &tab[i]);
    }

    // Ouvrir fichier binaire avec permissions : groupe écriture, autres lecture
    int fd = open("tab.bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWGRP | S_IROTH);
    if(fd == -1) 
    { 
        perror("open"); 
        return 1; 
    }

    write(fd, tab, n*sizeof(int)); // écrire le tableau
    close(fd);

    printf("Tableau sauvegardé dans tab.bin\n");
    free(tab);
    return 0;
}