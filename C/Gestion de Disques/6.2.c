#include <stdio.h>
#include <dirent.h>  // pour DIR et readdir
#include <sys/stat.h> // pour struct stat et stat()
#include <string.h>  // pour strcat, strcpy
#include <stdlib.h>  // pour exit

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage : %s <répertoire>\n", argv[0]);
        return 1;
    }

    DIR *d = opendir(argv[1]); // ouvrir le répertoire passé en argument
    if(!d) {
        perror("Erreur ouverture dossier");
        return 1;
    }

    struct dirent *file;

    // parcourir tous les fichiers du dossier
    while((file = readdir(d)) != NULL)
    {
        struct stat st;
        char path[1024];

        // construire le chemin complet : dossier + nom du fichier
        snprintf(path, sizeof(path), "%s/%s", argv[1], file->d_name);

        if(stat(path, &st) == -1) { // lire les infos du fichier
            perror("Erreur stat");
            continue;
        }

        // afficher uniquement les fichiers > 1 Mo
        if(st.st_size > 1024*1024) {
            printf("Fichier : %s, UID=%d, taille=%ld octets\n",
                   file->d_name, st.st_uid, st.st_size);
        }
    }

    closedir(d); // fermer le répertoire
    return 0;
}