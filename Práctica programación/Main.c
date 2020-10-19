#include <stdio.h>
#include "lib.h"


int main(int argc, char* argv[]){

    int numTok;
    char ptr[10000];
    char comando[1000];

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
    }
    printf("FIN\n" );
    return 0;
}