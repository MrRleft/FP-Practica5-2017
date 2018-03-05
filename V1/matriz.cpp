#include "matriz.h"
#include "checkML.h"

tMatriz matrizConstante(double x, int n){
	//Matriz tal que Aij=1/x , para todo i, j >0 y <tam. El tamaño viene definido ajeno a la función.
	tMatriz matriz;
	matriz.tam = n;
	for (int j = 0; j < n; j++){
		for (int i = 0; i < n; i++)
			matriz.matriz[i][j] = x;
	}
	return matriz;
}

tVector operator*(const tMatriz &m, const tVector &v){
	//Operador * redefinido para matriz-vector.
	tVector Resultado;
	double aux;
	Resultado.tam = v.tam;
	for (int j = 0; j < m.tam; j++){
		aux = 0;
		for (int i = 0; i < m.tam; i++){
			aux += m.matriz[j][i] * v.datos[i];
		}
		Resultado.datos[j] = aux;
	}
		
	return Resultado;
}

tMatriz operator*(double x, const tMatriz &m){
	//Operado * redefinido para escalar-matriz.
	tMatriz Resultado;
	Resultado.tam = m.tam;
	for (int j = 0; j < m.tam; j++){
		for (int i = 0; i < m.tam; i++){
			Resultado.matriz[j][i] = m.matriz[j][i] * x;
		}
	}
	return Resultado;
}

tMatriz operator+(const tMatriz &m1, const tMatriz &m2){
	//Operador + redefinido para suma de matrices.
	tMatriz Resultado;
	Resultado.tam = m1.tam;
	for (int j = 0; j < Resultado.tam; j++)
		for (int i = 0; i < Resultado.tam; i++)
			Resultado.matriz[j][i] = m1.matriz[j][i] + m2.matriz[j][i];
	return Resultado;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & L){
	// M' = L (1/total columna por cada elemento de la matriz)
	tMatriz Mprima, C, retorno;
	inicializarMatriz(Mprima);
	Mprima.tam = L.tam;
	double frac = (1.0 / L.tam);
	int N = L.tam;
	for (int j = 0; j < N; ++j) {
		double sumatorio = sumaColumnas(L, j);
		if (sumatorio == 0) {
			for (int i = 0; i < N; ++i)
				Mprima.matriz[i][j] =frac;
		}
		else {
			double fracNi = (1.0 / sumatorio);
			for (int i = 0; i < N; ++i) {
				if (L.matriz[i][j] == 1)
					Mprima.matriz[i][j] = fracNi;
			}
		}
	}
	C = matrizConstante(frac, N);
	retorno = (1 - c)*C + c*Mprima;
return retorno;
}

tVector normaliza(const tVector &v1){
	tVector result;
	result.tam = v1.tam;
	for (int k = 0; k < v1.tam; k++)
		result.datos[k] = v1.datos[k] / v1.datos[0];
	return result;
} // normaliza

tVector vectorPropio(const tMatriz &M, double epsilon){
	tVector v = vectorUnos(M.tam);
	tVector w = M * v;
	while (!proximos(v, w, epsilon))
	{
		v = w;
		w = M * v;
	}
	return normaliza(v);
} // vectorPropio

tVector valoresSubLista(const tListaCadenas &archivos, const tListaCadenas &enlaces, const tVector &v){
	tVector result = vectorUnos(0);
	int pos;
	for (int i = 0; i < archivos.tam; i++){
		string archivo = archivos.cadenas[i];
		pos = getPosicion(enlaces, archivo);
		annadir(result, v.datos[pos]);
	}
	return result;
} // valoresSubLista

void annadir(tVector &v, double e){
	//Añade el numero introducido e en el vector.
	v.datos[v.tam] = e;
	v.tam++;
} // annadir

//Funciones optativas V2
tVector vectorUnos(int tamC){
	//Esta funcion se encarga de crear un vector compuesto por unos del tamaño que le indiquemos.
	tVector unos;
	unos.tam = tamC;
	for (int i = 0; i < tamC; i++)
		unos.datos[i] = 1;
	return unos;
}

bool proximos(const tVector &v1, const tVector &v2, double epsilon) {
	int i = 0;
	while (i < v1.tam && abs(1 - v1.datos[i] / v2.datos[i]) < epsilon) {
	i++;
	}
	return i == v1.tam;
} // proximos

void inicializarMatriz(tMatriz &M){
	//Función para inicializar una matriz por referencia.
	M = matrizConstante(0, MAX_TAM);
}

void imprimir(tMatriz M) {
	//Función para imprimir una matriz;
	for (int i = 0; i < M.tam; ++i) {
		for (int j = 0; j < M.tam; ++j) {
			cout << M.matriz[i][j] << " ";
		}
		cout << "\n";
	}
}

double sumaColumnas(const tMatriz L, int columna) {
	//Calcula Nj
	double retorno = 0;
	for (int i = 0; i < L.tam; ++i) {
		if (L.matriz[i][columna] == 1)
			++retorno;
	}
	return retorno;
}