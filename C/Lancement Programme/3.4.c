#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char dirname[256];

    while(1) {
        printf("Nom du répertoire (ou 'quit' pour sortir) : ");
        scanf("%s", dirname);

        if(strcmp(dirname, "quit") == 0) 
            break;

        char command[512];
        snprintf(command, sizeof(command), "cp -r . %s", dirname);
        system(command);
    }

    return 0;
}