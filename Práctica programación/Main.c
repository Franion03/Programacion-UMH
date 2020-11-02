#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lib.h"


int main(int argc, char* argv[]){

    int numTok;
    char *ptr[1000];
    char comando[1000];
    char *prog="prog";
    char *sepf=" \n\t,.;:()[]";
    char *sep=" ";
    char *sepn=" \n\t,;:()[]";
    int aux;
    while(1){
        gets(comando);
        Trim(comando);
        if(comando==NULL || comando[0]=='\0')
            continue;
        numTok=0;
        ptr[numTok]=strtok (comando, " \n\t");
        numTok++;
        while( (ptr[numTok] = strtok( NULL, " \n\t")) != NULL)
        {
            numTok++;   
        }
        if(strcmp(ptr[0],"Exit")==0){
            break;
        }

        if(strcmp(ptr[0],prog)==0   ){
            
            if(numTok==1){    
                printf("%s\n",prog);
                printf("%s info\n",prog);
                printf("%s fichero cuenta palabra1 [palabra2] [palabra3] [palabra4] ...\n",prog);
                printf("%s fichero busca fichero2\n",prog);
                printf("%s fichero numeros\n",prog);
                printf("%s fichero fechas\n",prog);
                printf("%s fichero remplazar palabra1 palabra2\n",prog);
                printf("Exit\n");
            }

            else if(strcmp(ptr[1], "info")==0){
                if(numTok!=2){
                    Error();
                    continue;
                }
                printf("Nombre:Francisco Javier Quiles Ruiz\n");
                printf("Gmail:francisco.quiles05@goumh.umh.es\n");
            }
            
            else if(strcmp(ptr[2], "cuenta")==0){
                if(numTok <4){
                    Error();
                    printf("%i",numTok);
                    continue;
                }
                for (int i=3;i<numTok;i++){
                    aux=ContarToken(ptr[1],ptr[i],sepf);
                    printf("la palabra %s se repite %i veces\n",ptr[i],aux);
                }
            }

            else if(strcmp(ptr[2], "busca")==0){
                if(numTok <3){
                    Error();
                    continue;
                }
                Buscar (ptr[1],ptr[3],sepf);
            }
    
            else if(strcmp(ptr[2], "numeros")==0){
                if(numTok !=3){
                    Error();
                    continue;
                }
                Numeros(ptr[1],sepn);
            }

            else if(strcmp(ptr[2], "fechas")==0){
                if(numTok <3){
                    Error();
                    continue;
                }
            }

            else if(strcmp(ptr[2], "remplazar")==0){
                if(numTok <3){
                    Error();
                    continue;
                }
            }

            else {
                printf("%s",ptr[1]);
                Error();
            }
        }
        
    }
    printf("FIN\n" );
    return 0;
}