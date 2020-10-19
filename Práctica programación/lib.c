#include "lib.h"



void Trim(char *cad)
{
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
    println("Error parametros incorrectos");
    return;
}