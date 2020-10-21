#include <stdio.h>
#include "lib.h"


int main(int argc, char* argv[]){

    int numTok;
    char ptr[1000];
    char comando[1000];
    char prog="prog";

    while(1){
        gets(comando);
        Trim(comando);
        numTok=0;
        ptr[numTok]=strtok (comando, " \n\t");
        numTok++;
        while( (ptr[numTok] = strtok( NULL, " \n\t")) != NULL)
        {
            numTok++;   
        }

        if(strcmp(ptr[0],prog)==0   ){
            printf("%s\n",prog);
            printf("%s info\n",prog);
            printf("%s fichero cuenta palabra1 [palabra2] [palabra3] [palabra4] ...\n",prog);
            printf("%s fichero busca fichero2\n",prog);
            printf("%s fichero numeros\n",prog);
            printf("%s fichero fechas\n",prog);
            printf("%s fichero remplazar palabra1 palabra2\n",prog);
        }

        else if(strcmp(ptr[1], prog)==0){
            printf("Nombre:Francisco Javier Quiles Ruiz");
            printf("Gmail:francisco.quiles05@goumh.umh.es");
        }
    }
    printf("FIN\n" );
    return 0;
}