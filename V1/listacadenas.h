#ifndef listacadenas_h
#define listacadenas_h
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Definicion del tipo del struct de lista cadenas.
typedef string *tPuntCad;

typedef struct{
	tPuntCad cadenas;
	int tam;
	unsigned int cap;
} tListaCadenas;

//Funciones obligatorias V1
void insertar(tListaCadenas &lista, const string &s);
void eliminar(tListaCadenas &lista, int pos);
void imprimir(const tListaCadenas &lista);
int getTamanio(const tListaCadenas &lista);
bool buscar(const tListaCadenas &lista, const string &s);
string getCadena(const tListaCadenas &lista, int pos);

//Funciones optativas
void inicializar0(tListaCadenas &lista);
int getPosicion(const tListaCadenas &totales, string enlace);
void aumentaCapacidad(tListaCadenas &l);
#endif