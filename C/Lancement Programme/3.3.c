#include <stdio.h>
#include <stdlib.h>

int main()
{
    char filename[256];
    printf("Entrer le nom du fichier à ouvrir : ");
    scanf("%s", filename);

    char command[512];
    snprintf(command, sizeof(command), "/usr/bin/emacs %s", filename);
    system(command);

    return 0;
}