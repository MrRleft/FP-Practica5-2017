#include "clavevalor.h"
#include "matriz.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

//Funciones obligatorias V1
void crearTabla(tIndicePalabras & tabla, tListaCadenas & totales, const string & archivoInicial, tMatriz & L);

//Funciones extra
void AnadirTabla(tIndicePalabras &tabla, string archivo, tListaCadenas &visitados, tListaCadenas &noVisitados, tMatriz &L, tListaCadenas &totales);
void inicializarListasyTablas(tListaCadenas &visitados, tListaCadenas &noVisitados, tIndicePalabras &tabla);
void muestraArchivos(const tListaCadenas &archivos, const tVector &enlaces);
void ordenaValores(tListaCadenas &archivos, tVector &valores);
void comprobarPalabra(string &palabro);
string devolverEnlace(const string &palabro);
string pedirPalabra();
void getValor(const tIndicePalabras &tabla, string palabra, tListaCadenas &retorno);
