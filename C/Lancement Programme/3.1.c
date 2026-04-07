#include <stdio.h>

int main(int argc , char ** argv)
{ 
    if (argc == 3)
    {
        // Convertir d'abord les chaines de caracteres en entiers 
        int a = atoi(argv[1]);
        int b = atoi(argv[2]); 
        
        int s = a + b ;
        printf(" %d + %d = %d\n", a , b , s);

        return (0); 
    }

    else 
    {
        printf("Usage : %s nombre1 nombre2 " , argv[0]);
        return (1);
    }

}