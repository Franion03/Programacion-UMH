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
   /* while(1){
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
        }*/



            
            if(argc==1){    
                printf("%s\n",argv[0]);
                printf("%s info\n",argv[0]);
                printf("%s fichero cuenta palabra1 [palabra2] [palabra3] [palabra4] ...\n",argv[0]);
                printf("%s fichero busca fichero2\n",argv[0]);
                printf("%s fichero numeros\n",argv[0]);
                printf("%s fichero fechas\n",argv[0]);
                printf("%s fichero remplazar palabra1 palabra2\n",argv[0]);
                printf("Exit\n");
            }

            else if(strcmp(argv[1], "info")==0){
                if(argc!=2){
                    Error();
                    return 0;;
                }
                printf("Nombre:Francisco Javier Quiles Ruiz\n");
                printf("Gmail:francisco.quiles05@goumh.umh.es\n");
            }
            
            else if(strcmp(argv[2], "cuenta")==0){
                if(argc <4){
                    Error();
                    return 0;;
                }
                for (int i=3;i<argc;i++){
                    aux=ContarToken(argv[1],argv[i],sepf);
                    printf("la palabra %s se repite %i veces\n",argv[i],aux);
                }
            }

            else if(strcmp(argv[2], "busca")==0){
                if(argc <3){
                    Error();
                    return 0;;
                }
                Buscar (argv[1],argv[3],sepf);
            }

            else if(strcmp(argv[2], "numeros")==0){
                if(argc !=3){
                    Error();
                    return 0;;
                }
                Numeros(argv[1],sepn);
            }

            else if(strcmp(argv[2], "fechas")==0){
                if(argc <3){
                    Error();
                    return 0;;
                }
                BuscarFechas(argv[1],sepf);
            }

            else if(strcmp(argv[2], "remplazar")==0){
                if(argc !=5){
                    Error();
                    return 0;;
                }
            ReemplazarDatos(argv[1],argv[3],argv[4],sepf);
                
            }

            else {
                Error();
            }
        
        
    
    printf("FIN\n" );
    return 0;
}