//Practica 4 por Rubén Izquierdo y Javier Piernagorda, ambos del grupo G.
#include "checkML.h"
#include "indices.h"
#include "matriz.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tIndicePalabras idx;
	tListaCadenas totales, archivos;
	tMatriz L, M;
	tVector v, valores;
	string archivoInicial, palabra;
	ifstream file;
	
	cout << "Practica 4 por Ruben Izquierdo y Javier Piernagorda. \n";
	cout << "\n";
	cout << "Introduzca el nombre del fichero a partir del que se creara el indice: ";
	cin >> archivoInicial;
	cout << "\n";
	
	file.open(archivoInicial);
	if (file.is_open()) {
		
		inicializarMatriz(M);
		inicializar0(totales);
		insertar(totales, archivoInicial);
		crearTabla(idx, totales, archivoInicial, L);
		M = desdeEnlacesAMatriz(L); // M = (1 - C) * Cn + C * M´
		v = vectorPropio(M, 0.000001);
		palabra = pedirPalabra();
		
		while (palabra != "fin")	{
			inicializar0(archivos);
			getValor(idx, palabra, archivos);//Este se encarga de coger los enlaces para una palabra
			valores = valoresSubLista(archivos, totales, v);
			ordenaValores(archivos, valores); //Se encarga de ordenar los archivos en funcion de su valoracion de pagerank
			if (archivos.tam == 0) {
				cout << "\n";
				cout << "No se ha encontrado la palabra introducida. \n";
				cout << "\n";
			}
			else muestraArchivos(archivos, valores); //Se encarga de mostrar los asrchivos seguidos de su nombre.
			palabra = pedirPalabra();
			delete[] archivos.cadenas;
		}
		if (palabra == "fin") {
			delete[] totales.cadenas;
			for (int i = 0; i < idx.tam; ++i){
				delete[] idx.registro[i].valor.cadenas;
			}
			delete[] idx.registro;

			cout << " \n";
			file.close();
			system("pause");
		}
	}
	else{
		cout << "No se ha encontrado el archivo raiz. \n";
		system("pause");
	}
} // main