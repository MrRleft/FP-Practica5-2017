#include "listacadenas.h"
#include "checkML.h"

int getTamanio(const tListaCadenas &lista) {
	//Devuelve el tamaño actual de la lista de cadenas.
	return lista.tam;
}

string getCadena(const tListaCadenas &lista, int pos) {
	//Devuelve la cadena en la posicion solicitada (pos)
	return lista.cadenas[pos];
}

void insertar(tListaCadenas &lista, const string &s) {
	//Insertamos la cadena de caracteres s en la lista previa busqueda para ver si se guarda o ya existe
	if (!buscar(lista, s)) {
		if (lista.tam + 1== lista.cap) aumentaCapacidad(lista);
		lista.cadenas[lista.tam] = s;
		lista.tam++;
		
		
	}
}

bool buscar(const tListaCadenas &lista, const string &s) {
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < lista.tam){
		if (s == lista.cadenas[i]) encontrado = true;
		else i++;
	}
	return encontrado;
}

void eliminar(tListaCadenas &lista, int pos){
	//Elimina la cadena que haya en la posicion pos y desplaza todas las siguientes una posicion menos.
	for (int i = pos; i < lista.tam; i++){
		lista.cadenas[i] = lista.cadenas[i + 1];
	}
	lista.tam--;
	lista.cadenas[lista.tam] = "";
}

void imprimir(const tListaCadenas &lista){
	//Enseña en pantalla lo que hay en la lista.
	for (int i = 0; i < lista.tam; i++){
		cout <<"Encontrada en: " << lista.cadenas[i] << endl << endl;
	}
}

void inicializar0(tListaCadenas &lista){
	//Funcion para inicializar una lista a 0.
	//for (int i = 0; i < MAX; i++) lista.cadenas[i] = ""; //ANEXO1
	lista.tam = 0;
	lista.cap = 1;
	lista.cadenas = new string[1];
}

/*Anexo 1: Esto lo usariamos para borrar los datos de las cadenas, pero dado que quedan delimitados por el tam,
           no consideramos necesario hacerlo, ya que si en algun momento vamos a acceder a ello, los valores basura
           se sustituyen.*/

int getPosicion(const tListaCadenas &totales, string enlace) {
	//Devuelve la posicion del string solicitado (enlace) dentro de una lista de cadenas y -1 si no lo encuentra.
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < totales.tam) {
		if (enlace == totales.cadenas[i]) encontrado = true;
		else i++;
	}
	if (!encontrado)
		i = -1;
	return i;
}

void aumentaCapacidad(tListaCadenas &l){	
	//Aumenta la capacidad de la lista de cadenas.
	int *cap;
	cap = new int ((l.cap * 3) / 2 + 1);
	tPuntCad newDatos = new string[*cap];
	for (int i = 0; i < l.cap; i++)
	{
		newDatos[i] = l.cadenas[i];
	}
	tPuntCad oldDatos = l.cadenas;
	l.cadenas = newDatos;
	delete[] oldDatos;
	l.cap = *cap;
	delete cap;
} // aumentaCapacidad
