#include "clavevalor.h"
#include "listacadenas.h"
#include "checkML.h"

int getTamanio(const tIndicePalabras &idx){
	return idx.tam;
}

tRegistro getRegistro(const tIndicePalabras &idx, int pos){
	//Devuelve el registro de la posición indicada (pos).
	return idx.registro[pos];
}

bool buscar(const tIndicePalabras &idx, const string &s){ 
	/*Dado que ya tenemos otra funcion que se encarga exactamente de lo mismo que solamente devuelve
	  un entero, aqui lo que he hecho ha sido utilizar dicha funcion y hacer que me devuelva true 
	  o false en funcion de sus condiciones.*/
	bool encontrado;
	if (getPosicion(idx, s) == -1) encontrado = false;
	else encontrado = true;
	return encontrado;
}

int getPosicion(const tIndicePalabras &idx, const string &s){ 
	// Devuelve la posición del string solicitado con busqueda binaria recursiva aplicada.
	bool encontrado = false;
	int final = idx.tam - 1;
	int inicio = 0;
	return buscarR(idx, s, inicio, final);
}


int buscarR(const tIndicePalabras &idx, const string &buscado, int ini, int fin) {
	//Busqueda binaria recursiva.
	int pos = -1;
	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (buscado == idx.registro[mitad].clave) {
			pos = mitad;
		}
		else if (buscado < idx.registro[mitad].clave) {
			pos = buscarR(idx, buscado, ini, mitad- 1);
		}
		else {
			pos = buscarR(idx, buscado, mitad + 1, fin);
		}
	}
	return pos;
}



void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo){
	/*Lo que vamos a hacer aqui es ir insertando dentro de nuestro indice de palabras nuevas palabras en funcion de su clave. 
	  Si la clave ya existe actualizamos su lista de valores, si no, entonces lo que hacemos es
	  crear un nuevo registro para os dos, que ya iremos actualizando en el futuro.
	  A la hora de crear este registro, lo tendremos que insertar en el lugar adecuado para que 
	  se mantenga el orden dentro del registro de palabras*/
	int i = 0;
	if (!buscar(idx, palabra)) {
		if (idx.tam + 1 == idx.cap) aumentaCapacidad(idx);
		if (idx.tam == 0) {
			insertarCC(idx, palabra, nombreArchivo, i);
		}
		else {
			int i = 0;
			while (idx.registro[i].clave < palabra && idx.tam > i) {
				i++;
			}
			if (idx.registro[i].clave == "") {
				insertarCC(idx, palabra, nombreArchivo, i);
			}
			else {
				for (int j = idx.tam; j > i; j--) {
					idx.registro[j] = idx.registro[j - 1];
				//	inicializar0(idx.registro[j-1].valor); Valorar si usar esto
				}	
				insertarCC(idx, palabra, nombreArchivo, i);
			}
		}
	}
	else {//Actualizar registro
		int position;
		position = getPosicion(idx, palabra);
		insertar(idx.registro[position].valor, nombreArchivo);
	}
	
 }

void imprimir(const tIndicePalabras &idx) {
	for (int i = 0; i < idx.tam; ++i) {
		cout << "Palabra '" << idx.registro[i].clave << "'\n\n";
		imprimir(idx.registro[i].valor);
	}
}

//Funciones extra
void inicializar0(tIndicePalabras &idx){
	//Funcion de inicializar para un tIndicePalabras.
	idx.tam = 0;
	idx.cap = 1;
	idx.registro = new tRegistro[1];
}

void imprimirPos(const tIndicePalabras &idx, const int pos) {
	//Esta funcion se encargar de imprimir un registro unico de todo un indice de palabras
	cout << "Palabra '" << idx.registro[pos].clave << "'\n\n";
	imprimir(idx.registro[pos].valor);
}

void insertarCC(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo, int i) {
	/*Esta funcion se encarga de insertar en el indice de palabras la palabra y un nombre de archivo en el caso concreto en el que ya sepamos la posicion.
	  La he creado porque de esta manera nos evitamos el escribir el mismo codigo tres veces.*/
	idx.registro[i].clave = palabra;
	inicializar0(idx.registro[i].valor);
	insertar(idx.registro[i].valor, nombreArchivo);
	idx.tam++;
}

void aumentaCapacidad(tIndicePalabras &l){
	int *cap;
	cap = new int((l.cap * 3) / 2 + 1);
	tPuntReg newDatos = new tRegistro[*cap];
	for (int i = 0; i < l.cap; i++)
	{
		newDatos[i] = l.registro[i];
	}
	tPuntReg oldDatos = l.registro;
	l.registro = newDatos;
	delete[] oldDatos;
	l.cap = *cap;
	delete cap;

} // aumentaCapacidad
