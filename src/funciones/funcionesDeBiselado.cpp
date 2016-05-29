#include "Pila.h"
#include "Nodo.h"
#include "funcionesDeBiselado.h"

// Toma una lista de nodos y, segun los movimientos, los rota.
// Al final cambia la raiz inicial por la nueva.
void biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos, Nodo* raiz ){

	while (! movimientos -> getTamanio() == 1){
		
		if (movimientos -> getTamanio() >= 3){
		
			//rotacionDoble();
		
		} else {
		
			//rotacionTriple();
		
		}
	
	}
	
	
}
	// Hijo izquierdo de un hijo izquierdo
	// Hijo derecho de un hijo derecho
	// Hijo izquierdo de un hijo derecho
	// Hijo derecho de un hijo derecho
	// Hijo derecho
	// Hijo izquierdo
