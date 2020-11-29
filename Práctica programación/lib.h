#ifndef _LIB_H_
#define _LIB_H_
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>


void Trim(char *cad);
void Error();
int ContarToken( char *fichero, char *palabra, char *sep);
void Buscar(char *file, char *ficheroB, char *sep);
bool BuscarArray(char *palabras[], char *palabra, int nPalabras);
int FechaValida(char *cadena);//devuelve 1 si la fecha es válida
void Numeros(char *file, char *sep);
void BuscarFechas(char *file, char *sep);
void ReemplazarDatos(char *file,char *palabra1, char *palabra2, char *sep);
int Reemplazar(char*linea,char*palabra1,char*palabra2);
int FechaValidaAMD(char *cadena);
int Eliminar(char*linea,char*palabra1);
void EliminarDatos(char *file,char *palabra1, char *sep);
void MayusculaMin(char* palabra);
void OrdenarArray(char*Array[]);
void quicksort(int *V,int *O, int izq, int der);
int seleccionar_pivote(int *V, int izq, int der);
void intercambiar(int *V, int izq, int der);
void OrdenarNumeros(char*file, char*sep);






#endif