#ifndef clavevalor_h
#define clavevalor_h
#include "listacadenas.h"
#include <iostream>
#include <string>

using namespace std;

const int MAXI = 200;

//Definicion de los tipos de las estructuras registro e indicePalabras
typedef struct{
	string clave;
	tListaCadenas valor;
} tRegistro;

typedef tRegistro *tPuntReg;

typedef struct {
	tPuntReg registro;
	int tam;
	unsigned int cap;
} tIndicePalabras;

//Funciones obligatorias V1
void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo);
void imprimir(const tIndicePalabras &idx);
int getTamanio(const tIndicePalabras &idx);
int getPosicion(const tIndicePalabras &idx, const string &s);
bool buscar(const tIndicePalabras &idx, const string &s);
tRegistro getRegistro(const tIndicePalabras &idx, int pos);

//Funciones extra
void inicializar0(tIndicePalabras &idx);
void imprimirPos(const tIndicePalabras &idx, const int pos);
void insertarCC(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo, int i);
void aumentaCapacidad(tIndicePalabras &l);
int buscarR(const tIndicePalabras &idx, const string &buscado, int ini, int fin);

#endif