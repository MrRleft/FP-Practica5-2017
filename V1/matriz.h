#ifndef matriz_h
#define matriz_h

#include "listacadenas.h"
#include <iostream>
#include <string>
#include <iomanip>

//Declaracion tipos V2
const int MAX_TAM = 50;
const int MAX_DIM = 50;
const float c = 0.85;
typedef double tArrayBi[MAX_TAM][MAX_TAM];

typedef struct{
	tArrayBi matriz;
	int tam;
} tMatriz;

typedef struct{
	double datos[MAX_DIM];
	int tam;
} tVector;

//Funciones obligatorias de la version 2
tMatriz operator+(const tMatriz &m1, const tMatriz &m2);
tMatriz desdeEnlacesAMatriz(const tMatriz & L);
tMatriz operator*(double x, const tMatriz &m);
tMatriz matrizConstante(double x, int n);
tVector vectorPropio(const tMatriz & M, double epsilon);
tVector operator*(const tMatriz &m, const tVector &v);
tVector normaliza(const tVector & v);

//Funciones extra
void imprimir(tMatriz M);
void inicializarMatriz(tMatriz &M);
void annadir(tVector &v, double e);
double sumaColumnas(const tMatriz L, int columna);
bool proximos(const tVector &v1, const tVector &v2, double epsilon);
tVector vectorUnos(int numC);
tVector valoresSubLista(const tListaCadenas &archivos, const tListaCadenas &enlaces, const tVector &v);

#endif
