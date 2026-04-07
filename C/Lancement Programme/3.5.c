#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[256];

    while(1) {
        printf("Nom du fichier (ou 'quit' pour sortir) : ");
        scanf("%s", filename);

        if(strcmp(filename, "quit") == 0) break;

        char command[512];
        snprintf(command, sizeof(command), "/usr/bin/emacs %s", filename);
        system(command);
    }

    return 0;
}