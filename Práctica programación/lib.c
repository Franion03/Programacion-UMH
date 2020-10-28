#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"



void Trim(char *cad){
    int c, i, j;
    int  n=strlen(cad);
    if( cad == NULL || n<1 )
        return; 
    n--;
    while(n>=0 && ((c=cad[n])==' ' || c=='\t' || c=='\n' || c=='\r'))
        n--;
    cad[n+1]='\0';
    i=0;
    while(i<=n && ((c=cad[i])==' ' || c=='\t' || c=='\n' || c=='\r'))
        i++;
    for(j=0; j<n-i+2; j++)
        cad[j]=cad[j+i];
}

void Error(){
    printf("Error parametros incorrectos\n");
    return;
}

int ContarToken( char * fichero, char *palabra, char *sep){
    FILE *f=fopen(fichero,"r");
    char linea[1000];
    int tamSep=strlen(sep);
    char *p2;
    int numeroTokens=0;
    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return 0;
    }
    
    while(!feof(f)){
        fgets(linea,10000,f);
        p2=strtok(linea,sep);
        while(p2!=NULL){
            if(strcmp(palabra,p2)==0){
                numeroTokens++;
            }
            p2=strtok(NULL,sep);
        }

    }
    fclose(f);
    return numeroTokens;
}

void Buscar(char *file, char *ficheroB,char *sep){
    char linea[10000];
    char *p2;
    int i, numPalabras=100000;
    FILE *fich=(file,"r");
    if(fich==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(fich);
        return 0;
    }

    FILE *fichB=(ficheroB,"r");
        if(fichB==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(fichB);
        return 0;
    }
    char **palabras=malloc(sizeof(char*)*numPalabras);
    //Recorremos el segundo fichero en busca de las palabras
    while(!feof(fichB)){
        fgets(linea,10000,fichB);
        p2=strtok(linea,sep);
        while(p2!=NULL){
            //comprobamos si la palabra existe en el array de palabras a buscar
            for (i=0;i<numPalabras;i++){
                if(strcmp(palabras[i],p2)==0){
                   break;
                }
                else
                    palabras = strdup(p2);
            }
            p2=strtok(NULL,sep);
        }

    }
    fclose(fichB);


    //Combrobamos las veces que se repiten los caracteres en el otro fichero










    //Liberamos memoria
    
}