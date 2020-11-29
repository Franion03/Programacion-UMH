#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>
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

    if(cadena == NULL || strlen(cadena) != 10)
    return 0;
  
  	a=(cadena[6]-'0')*1000 +(cadena[7]-'0')*100+(cadena[8]-'0')*10+ (cadena[9]-'0');
    m=(cadena[3]-'0')*10 +(cadena[4]-'0');
    d=(cadena[0]-'0')*10 +(cadena[1]-'0');
    
   error=0;
   for (i=0; i<10; i++)
    {
        if(i==2 || i==5){

            if(cadena[i] != '/')
                return 0;
        }
        else{

            if(cadena[i] < '0' || cadena[i] > '9')
                return 0;
        }

    }

    if (strlen(cadena)!=10)
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
            cont=0;
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
                if(p[0]=='+'){
                    for(i=1;i<strlen(p);i++){
                        if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
                            
                        break;
                        }
                        else if(p[i]=='.'){
                        cont++;   
                        }
                    }
                }
                else{
                    for(i=0;i<strlen(p);i++){
                        if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
                            
                        break;
                        }
                        else if(p[i]=='.'){
                        cont++;   
                        }
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
    //printf("Existen %i numeros negativos, %i numeros positivos, %i numeros enteros , %i numeros reales \n",numNeg,numPos,numEnt,numReal);
    printf("Existen: %i numeros\n",numPos+numNeg);
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
    int contador=0;

    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return ;
    }
    //Comprobamos el nombre del fichero si el último grupo de carcteres es (numero) se cambia por numero++
    char nuevof[1000];
    char extension[100];
    char nombre[1000];
    int n=1;
    p=strstr(file,".");
    strcpy(extension,p);

    strncpy(nombre,file,p-file);
    nombre[p-file]='\0';
    while((p=strstr(p+1,"."))!=NULL){
        strcpy(extension,p);
        strncpy(nombre,file,p-file);
    }
    sprintf(nuevof,"%s_new%s",nombre,extension);
    FILE*fn=fopen(nuevof,"r");
    while(fn!=NULL){
        fclose(fn);
        n++;
        sprintf(nuevof,"%s_new(%d)%s",nombre,n,extension);
        fn=fopen(nuevof,"r");
    }
    fn=fopen(nuevof,"w");
    
    while(!feof(f)){
        fgets(linea,10000,f);
        Trim(linea);
        contador=contador+Reemplazar(linea,palabra1,palabra2);
        fprintf(fn,"%s\n",linea);
    }
    //Creamos el nuevo fichero y lo recorremos con las palabras para encontrar la deseada
    /*while(!feof(f)){
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
    }*/
    fclose(f);
    fclose(fn);
    printf("la palabra %s se ha cambiado por %s , %i veces\n",palabra1,palabra2,contador);
}

int Reemplazar(char*linea,char*palabra1,char*palabra2){
    int nPalabra1=strlen(palabra1);
    int npalabra2=strlen(palabra2);
    char*p=strstr(linea,palabra1);
    char*paux;
    char linea2[10000];
    char aux[10000];
    int contador=0;
    if(p!=NULL) {
        strncpy(linea2,linea,p-linea);
        linea2[p-linea]='\0';
        paux=p+nPalabra1;
        strcat(linea2,palabra2); 
        contador++;
        while((p=strstr(p+nPalabra1,palabra1))!=0){
            strncpy(aux,paux,p-paux);
            aux[p-aux]='\0';
            strcat(linea2,aux);
            strcat(linea2,palabra2);
            paux=p+nPalabra1;
            contador++;
        }
    }
    else return 0;
    strcat(linea2,paux);
    strcpy(linea,linea2);
    return contador;
}

int FechaValidaAMD(char *cadena)
{
	
  int i, d, m, a;
  int error;

    if(cadena == NULL || strlen(cadena) != 10)
    return 0;
  
  	a=(cadena[0]-'0')*1000 +(cadena[1]-'0')*100+(cadena[2]-'0')*10+ (cadena[3]-'0');
    m=(cadena[5]-'0')*10 +(cadena[6]-'0');
    d=(cadena[8]-'0')*10 +(cadena[9]-'0');
    
   error=0;
   for (i=0; i<10; i++)
    {
        if(i==4 || i==7){

            if(cadena[i] != '/')
                return 0;
        }
        else{

            if(cadena[i] < '0' || cadena[i] > '9')
                return 0;
        }

    }

    if (strlen(cadena)!=10)
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

int Eliminar(char*linea,char*palabra1){
    int nPalabra1=strlen(palabra1);
    char*p=strstr(linea,palabra1);
    char*paux;
    char linea2[10000];
    char aux[10000];
    int contador=0;
    if(p!=NULL) {
        strncpy(linea2,linea,p-linea);
        linea2[p-linea]='\0';
        paux=p+nPalabra1;
        contador++;
        while((p=strstr(p+nPalabra1,palabra1))!=0){
            strncpy(aux,paux,p-paux);
            aux[p-aux]='\0';
            strcat(linea2,aux);
            paux=p+nPalabra1;
            contador++;
        }
    }
    else return 0;
    strcat(linea2,paux);
    strcpy(linea,linea2);
    return contador;
}

void EliminarDatos(char *file,char *palabra1, char *sep){
        FILE *f=fopen(file,"r");
    char linea[10000];
    char *p;
    int contador=0;

    if(f==NULL){
        printf("Error, no se ha especificado fichero\n");
        fclose(f);
        return ;
    }
    //Comprobamos el nombre del fichero si el último grupo de carcteres es (numero) se cambia por numero++
    char nuevof[1000];
    char extension[100];
    char nombre[1000];
    int n=1;
    p=strstr(file,".");
    strcpy(extension,p);

    strncpy(nombre,file,p-file);
    nombre[p-file]='\0';
    while((p=strstr(p+1,"."))!=NULL){
        strcpy(extension,p);
        strncpy(nombre,file,p-file);
    }
    sprintf(nuevof,"%s_new%s",nombre,extension);
    FILE*fn=fopen(nuevof,"r");
    while(fn!=NULL){
        fclose(fn);
        n++;
        sprintf(nuevof,"%s_new(%d)%s",nombre,n,extension);
        fn=fopen(nuevof,"r");
    }
    fn=fopen(nuevof,"w");
    
    while(!feof(f)){
        fgets(linea,10000,f);
        Trim(linea);
        contador=contador+Eliminar(linea,palabra1);
        fprintf(fn,"%s\n",linea);
    }
    //Creamos el nuevo fichero y lo recorremos con las palabras para encontrar la deseada
    /*while(!feof(f)){
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
    }*/
    fclose(f);
    fclose(fn);
    printf("la palabra %s se ha eliminado  , %i veces\n",palabra1,contador);
}

void MayusculaMin(char* palabra){
    int i;
    int len=strlen(palabra);
    char* aux ;
    strcpy(aux,palabra);
    for (i=0;i<len;i++){
        aux[i]=tolower(aux[i]);
    }
    strcpy(palabra,aux);
}

void OrdenarNumeros(char*file, char*sep){
    FILE *f=fopen(file,"r");
    int pos=0, i, cont=0;
    char linea[10000];
    char *p;
    int *n=malloc(3*sizeof(int));
    char aux[100];

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
            cont=0;
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
                    strcpy(aux,p);
                    n[pos]=atoi(aux);
                    pos++;
                }
                else if(cont==1 && i==strlen(p)){
                    strcpy(aux,p);
                    n[pos]=atoi(aux);
                    pos++;
                }
            }
            //si no es negativo asumimos que es positivo y hacemos las mismas comprobaciones
            else {
                if(p[0]=='+'){
                    for(i=1;i<strlen(p);i++){
                        if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
                            
                        break;
                        }
                        else if(p[i]=='.'){
                        cont++;   
                        }
                    }
                }
                else{
                    for(i=0;i<strlen(p);i++){
                        if((p[i] < '0' || p[i] > '9') && p[i] != '.'){
                            
                        break;
                        }
                        else if(p[i]=='.'){
                        cont++;   
                        }
                    }
                }
                if(cont==0 && i==strlen(p)){
                    strcpy(aux,p);
                    n[pos]=atoi(aux);
                    pos++;
                }
                else if(cont==1 && i==strlen(p)){
                    strcpy(aux,p);
                    n[pos]=atoi(aux);
                    pos++;
                }
            }
            p=strtok(NULL,sep);
        }
    }
    fclose(f);
    //printf("Existen %i numeros negativos, %i numeros positivos, %i numeros enteros , %i numeros reales \n",numNeg,numPos,numEnt,numReal);
   for(i = 0; i < pos; i++)
    {
       printf("%i\n",n[i]);
    }
    int*nord=malloc(3*sizeof(int));
    for(i = 0; i < pos; i++)
    {
         nord[i]=n[i];
    }
    quicksort(n,nord,0,pos-1);
    for(i = 0; i < pos; i++)
    {
       printf("/%i\n",nord[i]);
    }
}

void quicksort(int *V, int *O,int izq, int der)
{
    int i, d, p;

    int pivote;

    p=seleccionar_pivote(V, izq, der);

    if (p > 0)
    {
        pivote=V[p];
        i=izq;
        d=der;
        while(i<=d)
        {
            while(V[i]<pivote)
            {
                i=i+1;
            }

            while(V[d]>pivote)
            {
                d=d-1;
            }

            if(i<=d)
            {
                intercambiar(V,i,d);
                intercambiar(O,i,d);
                i=i+1;
                d=d-1;
            }
        }

        if(izq<d)
            quicksort(V,O, izq,d);
        if(i<der)
            quicksort(V,O, i,der);
    }
}

int seleccionar_pivote(int *V, int izq, int der)
{
    int centro=(izq+der)/2,
         V_izq=V[izq],
        V_cen=V[centro],
        V_der=V[der];

    if((V_izq<V_cen && V_izq>V_der) || (V_izq>=V_cen && V_izq<=V_der))
    {
        return izq;
    }
    else if((V_cen<=V_izq && V_cen>=V_der) || (V_cen>=V_izq && V_cen<=V_der))
    {
        return centro;
    }
    else
    {
        return der;
    }

    return 0;
}

void intercambiar(int *V, int izq, int der)
{
    int Temp=V[izq];

    V[izq]=V[der];
    V[der]=Temp;
}

int buscaPref(char *palabras, int nPal, FILE *f ,char*sep)
{
    int cuenta = 0;
    int j=0;
    int correcto=0;
    char linea[nPal];
    while(fgets(linea,nPal,f) != NULL)
    {
        char *p = linea;
        char *tok = strtok (p, sep);
        while (tok != NULL) 
        {
            if (strcmp(tok, palabras)==0)
            {
                correcto=1;
            }
            else
            {
                for (int i = 0; i < strlen(palabras); i++)
                {                
                    j=strlen(palabras)-i-1;
                    if (palabras[j]==tok[j])
                    {
                        correcto=1;
                    }
                    else 
                    {
                        correcto=0; break;
                    }
                }           
            }
            if (correcto==1)
            {
                correcto==0;
                cuenta++;
                ++p;
            }
            tok = strtok (NULL, sep);
        }
    }
    return cuenta;
}

void cuentaPref(char *nomFich, int nPal, char *palabras[])
{
    int i;
    FILE *f = fopen(nomFich,"r");

	if (f==NULL)
	{
        printf ("Error, el nombre del fichero es erroneo o no existe\n");
        return;
	}

	else
	{
   		for ( i = 0; i < nPal; i++)
   		{
       		printf("'%s' : %d  \n", palabras[i], buscaPref( palabras[i], MAX, f,sep));
       		rewind(f);
   		}
	}
	fclose(f);
    
}


int buscaSuf(char *palabras, int nPal, FILE *f ,char*sep)
{
    int cuenta = 0;
    int j=0;
    int correcto=0;
    char linea[nPal];
    while(fgets(linea,nPal,f) != NULL)
    {
        char *p = linea;
        char *tok = strtok (p, sep);
        while (tok != NULL) 
        {
            if (strcmp(tok, palabras)==0)
            {
                correcto=1;
            }
            else
            {
                for (int i = 0; i < strlen(palabras); i++)
                {                
                    j=strlen(palabras)-i-1;
                    if (palabras[j]==tok[strlen(tok)-i-1])
                    {
                        correcto=1;
                    }
                    else 
                    {
                        correcto=0; 
                        break;
                    }                
                }            
            }
            if (correcto==1)
            {
                correcto==0;
                cuenta++;
                ++p;
            }       
            tok = strtok (NULL, sep);
        }
    }
    return cuenta;
}

void cuentaSuf(char *nomFich, int nPal, char *palabras[] ,char*sep)
{
    int i;
    FILE *f = fopen(nomFich,"r");

	if (f==NULL)
	{
   	    printf ("Error, el nombre del fichero es erroneo o no existe\n");
        return;
	}

	else
	{
   		for ( i = 0; i < nPal; i++)
   		{
       		printf("'%s' : %d  \n", palabras[i], buscaSuf( palabras[i], MAX, f,sep));
       		rewind(f);
   		}    
	}
	fclose(f);
}