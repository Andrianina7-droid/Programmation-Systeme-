#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("tab.bin", "rb");
    if(!f) { perror("fopen"); return 1; }

    int *tab = NULL;
    int capacity = 10;
    int n = 0;
    tab = malloc(capacity * sizeof(int));

    int x;
    while(fread(&x, sizeof(int), 1, f) == 1) {
        if(n >= capacity) {
            capacity *= 2;
            tab = realloc(tab, capacity * sizeof(int));
        }
        tab[n++] = x;
    }

    printf("Tableau chargé (%d entiers) :\n", n);
    for(int i=0;i<n;i++) printf("%d ", tab[i]);
    printf("\n");

    free(tab);
    fclose(f);
    return 0;
}