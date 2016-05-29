#include "Pila.h"
#include "Nodo.h"
#include "funcionesDeBiselado.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Pila.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Nodo.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/funcionesDeBiselado.h"
// Toma una lista de nodos y, segun los movimientos, los rota.
// Al final cambia la raiz inicial por la nueva.
void biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos, Nodo* raiz ){

	while (! movimientos -> getTamanio() == 1){

		if (movimientos -> getTamanio() >= 3){

			rotacionDoble(nodos, movimientos);

		} else {

			rotacionTriple(nodos, movimientos);

		}

	}

}

// Funciones internas privadas.

void rotacionDoble(Pila<Nodo*>* nodos, Pila<char>* movimientos){

	// Tres nodos a rotar.
	//Nodo* hijo;
	//Nodo* padre;
	//Nodo* abuelo;
	// Movimientos.
	// Vuelvo a poner a la raiz;

}

void rotacionTriple(Pila<Nodo*>* nodos, Pila<char>* movimientos){

};
	// Hijo izquierdo de un hijo izquierdo
	// Hijo derecho de un hijo derecho
	// Hijo izquierdo de un hijo derecho
	// Hijo derecho de un hijo derecho
	// Hijo derecho
	// Hijo izquierdo
