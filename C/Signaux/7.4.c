#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n;
    printf("Nombre d'éléments : ");
    scanf("%d", &n);

    int *tab = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    int i;
    while(1) {
        printf("Index à afficher : ");
        scanf("%d", &i);
        if(i>=0 && i<n) {
            printf("tab[%d] = %d\n", i, tab[i]);
            break;
        } else {
            printf("Erreur : index invalide !\n");
        }
    }

    free(tab);
    return 0;
}