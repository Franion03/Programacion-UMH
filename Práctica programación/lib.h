#ifndef _LIB_H_
#define _LIB_H_
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void Trim(char *cad);
void Error();
int ContarToken( char * fichero, char *palabra, char *sep);
void Buscar(char * file, char *ficheroB, char *sep);
bool BuscarArray(char*palabras[], char* palabra, int nPalabras);









#endif