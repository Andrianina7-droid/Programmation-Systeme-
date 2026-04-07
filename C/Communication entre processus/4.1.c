#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

int main() 
{
    int p1[2] , p2[2];
    pipe(p1);
    pipe(p2);

    pid_t pid = fork();

    if(pid == 0)
    {
        char word[100]; 
        printf("Entrez un mot : ");
        scanf("%s", word);

        write(p1[1], word, strlen(word)+1);

        int results;
        read(p2[0], &results, sizeof(int));

        printf("Résultat : %d\n", results);

        exit(0);
    }
    else
    {   

        char word[100];
        read(p1[0], word, sizeof(word));

        FILE *f = fopen("file.txt", "r");

        if(f == NULL)
        {
            perror("Erreur ouverture fichier");
            exit(1);
        }

        char line[100];
        int found = 0;

        while(fscanf(f, "%s", line) != EOF)
        {
            if(strcmp(word, line) == 0)
            {
                found = 1;
                break;
            }
        }

        fclose(f);

        write(p2[1], &found, sizeof(int));

        wait(NULL);
    }

    return (0);
}