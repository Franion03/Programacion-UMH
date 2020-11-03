#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    char linea[10000];
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
        Trim(linea);
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
    char *p2,*p1;
    int i, numPalabras=0,numTokens;


    FILE *fichB=fopen(ficheroB,"r");
    if(fichB==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(fichB);
        return ;
    }
    char **palabras=malloc(sizeof(char*)*1000);
    //Recorremos el segundo fichero en busca de las palabras
    while(!feof(fichB)){
        fgets(linea,10000,fichB);
        Trim(linea);
        p2=strtok(linea,sep);
        while(p2!=NULL){
            //comprobamos si la palabra existe en el array de palabras a buscar
            if(!BuscarArray(palabras,p2,numPalabras)){
                palabras[numPalabras] = strdup(p2);
                numPalabras++;
            }
            p2=strtok(NULL,sep);
        }

    }
    fclose(fichB);
    FILE *fich=fopen(file,"r");
    if(fich==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(fich);
        return ;
    }

    //Combrobamos las veces que se repiten los caracteres en el otro fichero
    for (i=0;i<numPalabras;i++){
        fseek(fich,0,SEEK_SET);
        numTokens=0;
        while (!feof(fich)){
            fgets(linea ,10000,fich);
            Trim(linea);
            p1=strtok(linea,sep);
            while(p1!=NULL){
                if(strcmp(palabras[i],p1)==0){
                    numTokens++;
                }
                p1=strtok(NULL,sep);
            }

        }
        printf("La palabra %s se repite %i veces\n",palabras[i],numTokens);
    }
    fclose(fich);
    //Liberamos memoria
    for (i=0;i<numPalabras;i++){
        free(palabras[i]);
    }
    free(palabras);
    
}

bool BuscarArray(char*palabras[], char* palabra,int nPalabras){
    for (int i=0;i<nPalabras;i++){
        if(strcmp(palabras[i],palabra)==0){
            return true;
        }
    }
    return false;

}

int FechaValida(char *cadena)
{
	
  int i, d, m, a;
  int error;

  
  
  	a=(cadena[6]-'0')*1000 +(cadena[7]-'0')*100+(cadena[8]-'0')*10+ (cadena[9]-'0');
    m=(cadena[3]-'0')*10 +(cadena[4]-'0');
    d=(cadena[0]-'0')*10 +(cadena[1]-'0');
    
   error=0;
   for (i=0; i<10; i++)
    {
        if(i!=4 && i!=7)
        {
            if ((cadena[i]<'0' || cadena [i]>'9') && cadena[i]!='/' /*|| cadena[i]!='-')*/)
            error=1;
        }

    }
    if (error==1)
       return 0;
    else if (strlen(cadena)!=10)
       return 0;
    else if(d<1 || m<1 || a<1 || d>31 || m>12 || a>9999 )
       return 0;
    else if((m==4 || m==6 || m==9|| m==11) && d>30)
       return 0;
    else if (m==2 && a%4==0 && d>29)
       return 0;
    else if (m==2 && a%4!=0 && d>28)
       return 0;
    else 
       return 1;
} 

void Numeros(char*file, char*sep){
    FILE *f=fopen(file,"r");
    int numPos=0, numNeg=0, numEnt=0, numReal=0, i, cont=0;
    char linea[10000];
    char *p;

    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return ;
    }
// recorremos la totalidad del fichero
    while(!feof(f)){
        fgets(linea,10000,f);
        Trim(linea);
        p=strtok(linea,sep);
        //Comprobamos cada token de la linea
        while(p!=NULL){
            //comprobamos si el token es negativo
            if(p[0] == '-'){
                for( i = 1 ; i < strlen(p) ; i++ ){
                    if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
            
                     break;
                    }
                    else if(p[i]=='.'){
                    cont++;   
                    }
                }
                if(cont==0 && i==strlen(p)){
                    numNeg++;
                    numEnt++;
                }
                else if(cont==1 && i==strlen(p)){
                    numNeg++;
                    numReal++;
                }
            }
            //si no es negativo asumimos que es positivo y hacemos las mismas comprobaciones
            else {
                for(i=0;i<strlen(p);i++){
                    if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
                        
                     break;
                    }
                    else if(p[i]=='.'){
                    cont++;   
                    }
                }
                if(cont==0 && i==strlen(p)){
                    numPos++;
                    numEnt++;
                }
                else if(cont==1 && i==strlen(p)){
                    numPos++;
                    numReal++;
                }
            }
            p=strtok(NULL,sep);
        }
    }
    fclose(f);
    printf("Existen %i numeros negativos, %i numeros positivos, %i numeros enteros , %i numeros reales \n",numNeg,numPos,numEnt,numReal);
}

void BuscarFechas(char *file, char *sep){
    FILE*f=fopen(file,"r");
    char linea[10000];
    int nfechas=0;
    char *p;

    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return ;
    }

    while (!feof(f)){
        fgets(linea,10000,f);
        Trim(linea);
        p=strtok(linea,sep);
        while(p!=NULL){
            if(FechaValida(p)==1){
                nfechas++;
            }
            p=strtok(NULL,sep);
        }
    }
    fclose(f);
    printf("existen %i fechas validas para el formato:DD/MM/AAAA \n",nfechas);
}

void ReemplazarDatos(char *file,char *palabra1, char *palabra2, char *sep){
    FILE *f=fopen(file,"r");
    char linea[10000];
    char *p;

    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return ;
    }
    //Comprobamos el nombre del fichero si el último grupo de carcteres es (numero) se cambia por numero++
    char*nuevof="Hey";
    char*numero;
    int n,numCambios=0;
    if(1==0){
        n=atoi(numero);
        n=n++;
       // nuevof=strcat("()");
    }
    else strcpy(nuevof,strcat(file,"(1)"));
    //Creamos el nuevo fichero y lo recorremos con las palabras para encontrar la deseada
    FILE *fn=fopen(nuevof,"w");
    while(!feof(f)){
        fgets(linea,10000,f);
        Trim(linea);
        p=strtok(linea,sep);
        while(p!=NULL){
            if(strcmp(palabra1,p)==0){
                fprintf(fn,"%s%c",palabra2,p[strlen(p)]);
                numCambios++;
            }
            else fprintf(fn,"%s",p);
            p=strtok(NULL,sep);
        }
        fprintf(fn,"\n");   
    }
    fclose(f);
    fclose(fn);
    printf("la palabra %s se ha cambiado por %s , %i veces\n",palabra1,palabra2,numCambios);
}