#include "indices.h"
#include "clavevalor.h"
#include "Matriz.h"
#include "checkML.h"

void crearTabla(tIndicePalabras & tabla, tListaCadenas & totales, const string & archivoInicial, tMatriz & L){
	/*Esta funcion se encarga de leer el archivo principal y de ir cogiendo los enlaces que aparezcan
	en el e ir metiendolos en los diferentes arrays.*/
	tListaCadenas visitados, noVisitados;	
	inicializarMatriz(L);
	L.tam = 1;
	inicializarListasyTablas(visitados, noVisitados, tabla);
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	while (noVisitados.tam > 0){
		AnadirTabla(tabla, noVisitados.cadenas[0], visitados, noVisitados, L, totales);
		insertar(visitados, noVisitados.cadenas[0]);
		eliminar(noVisitados, 0);		
	}
	delete []  visitados.cadenas;
	delete [] noVisitados.cadenas;
}

//Funciones añadidas

void AnadirTabla(tIndicePalabras &tabla, string archivo, tListaCadenas &visitados, tListaCadenas &noVisitados, tMatriz &L, tListaCadenas &totales) {
	/*Esta funcion lo que hace es encargarse de cargar en la tabla lo que sea que hay en el archivo
	que entre, sea cual sea*/
	int i;
	int j;
	ifstream file;
	string palabro, enlace;
	file.open(archivo);
	while (!file.eof()) {
		file >> palabro;
		//Si el primer caracter indica un enlace
		if (palabro[0] == '<') {
			//Obtencion del enlace, sin "<" ni ">"
			enlace = devolverEnlace(palabro);
			//Una vez obtenido el enlace puro, comprobamos si está en visitados o en noVisitados, y en caso de no estar ahí, añadimos.
			if (buscar(totales, enlace)) {
				j = getPosicion(totales, archivo);
				i = getPosicion(totales, enlace);
				L.matriz[i][j] = 1.0;
			}
			else {
				insertar(totales, enlace);
				insertar(noVisitados, enlace);
				++L.tam;
				j = getPosicion(totales, archivo);
				L.matriz[L.tam - 1][j] = 1.0;
			}
		}
		//Si es una palabra cualquiera que no empieza por "<" procedemos a guardarla.
		else {
			comprobarPalabra(palabro); //Lo primero es normalizarla.
			insertar(tabla, palabro, archivo);
		}

	}
	file.close();
}

void comprobarPalabra(string &palabro) {
	/*La funcion recibe un string (palabro) y comprueba que sea una palabra valida. En caso de no serlo (por ej, recibe "edificio.", devolveremos 
	simplemente "edificio", ya que el punto no es parte de la palabra) un string retorno que será palabro como una palabra de verdad
	Supondremos que el texto está bien escrito y que no se da el caso de un punto delante de una palabra.*/
	int lastpos = palabro.length() - 1;
	if (palabro[lastpos] == '.' || palabro[lastpos] == ',') {
		palabro = palabro.substr(0, lastpos);
	}
	//std::transform(myString.begin(), myString.end(), myString.begin(),std::tolower);
	transform(palabro.begin(), palabro.end(), palabro.begin(), tolower);
}

string devolverEnlace(const string &palabro) {
	//Esta funcion se encarga de devolverte el enlace sin los simbolos "<" y ">". 
	string enlace;
	int longitud = palabro.length();
	longitud = longitud - 2;
	enlace = palabro.substr(1, longitud);
	transform(enlace.begin(), enlace.end(), enlace.begin(), tolower);
	return enlace;
}

void inicializarListasyTablas(tListaCadenas &visitados, tListaCadenas &noVisitados, tIndicePalabras &tabla){
	//Inicializamos las listas.
	inicializar0(visitados);
	inicializar0(noVisitados);
	inicializar0(tabla);
}

string pedirPalabra(){
	//Solicita al usuario una palabra a buscar en idx.
	string palabro;
	cout << "Escribe la palabra a buscar (fin = salir): ";
	cin >> palabro;
	transform(palabro.begin(), palabro.end(), palabro.begin(), tolower);
	return palabro;
}

void getValor(const tIndicePalabras &tabla, string palabra, tListaCadenas &retorno) {
	//Modifica y copia una lista de enlaces para una palabra solicitada en otra lista de cadenas "retorno".
	int pos = getPosicion(tabla, palabra);
	if (pos != -1) 
		for (int i = 0; i < tabla.registro[pos].valor.tam; i++)
			insertar(retorno, tabla.registro[pos].valor.cadenas[i]);
	else retorno.tam = 0;
}

void ordenaValores(tListaCadenas &archivos, tVector &valores) {
	//Ordena los valores del vector.
	int max = valores.tam;
	max = max - 1;
	for (int i = 0; i < max; i++) {
		int mayor = i;
		for (int j = i + 1; j < valores.tam; j++) {
			if (valores.datos[j] > valores.datos[mayor]) {
				mayor = j;
			}
		}
		if (mayor > i) {
			double tmp1;
			string tmp2;
			tmp1 = valores.datos[i];
			valores.datos[i] = valores.datos[mayor];
			valores.datos[mayor] = tmp1;
			tmp2 = archivos.cadenas[i];
			archivos.cadenas[i] = archivos.cadenas[mayor];
			archivos.cadenas[mayor] = tmp2;
		}
	}
}

void muestraArchivos(const tListaCadenas &archivos, const tVector &enlaces) {
	//Muestra al usuario en qué archivos se ha encontrado la palabra que busca y su PageRank.
	cout << "\n";
	for (int i = 0; i < archivos.tam; i++) {
		cout << "Aparece en el archivo '" << archivos.cadenas[i] << "' con un PageRank de " << enlaces.datos[i] << ".\n";
		cout << "\n";
	}
}

