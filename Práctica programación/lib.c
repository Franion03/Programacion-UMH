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
    char* linea[1000];
    int tamSep=strlen(sep);
    char *p1,*p2;
    int numeroTokens=0;
    if(f==NULL){
        printf("Error, no se ha especificado fichero, usa antes el comando 'Datos'\n");
        fclose(f);
        return 0;
    }
    
    while(feof){
        fgets(linea,10000,f);
        p2=strstr(linea,sep);
        while(p2!=NULL){
            if(strcmp(palabra,p2)==0){
                numeroTokens++;
            }
            p1=p2+tamSep;
            p2=strstr(p1,sep);
        }

    }
    fclose(f);
    return numeroTokens;
}