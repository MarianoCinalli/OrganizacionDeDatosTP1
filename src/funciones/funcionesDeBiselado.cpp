#include "funcionesDeBiselado.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Pila.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Nodo.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/funcionesDeBiselado.h"


// 9 de cada 10 doctores recomiendan ver la documentacion,
// para entender como funciona esto.

// Toma una lista de nodos y, segun los movimientos, los rota.
// Al final cambia la raiz inicial por la nueva, devuelve ambas pilas vacias.
void biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos, Nodo* raiz ){
	
	int cantidadDeNodos = nodos -> getTamanio();
	
	while (! (cantidadDeNodos == 1) ){
		
		if (cantidadDeNodos >= 3){

			rotacionDoble(nodos, movimientos);

		} else {
		
			rotacionSimple(nodos, movimientos);

		}

	}
	
	raiz = nodos -> desapilar();

}

// Funciones internas, privadas. ---------------------------------------

void rotacionDoble(Pila<Nodo*>* nodos, Pila<char>* movimientos){

	// Tres nodos a rotar.
	Nodo* hijo = nodos -> desapilar();
	Nodo* padre = nodos -> desapilar();
	Nodo* abuelo = nodos -> desapilar();
	
	// Movimientos.

	char padreAHijo = movimientos -> desapilar();
	char abueloAPadre = movimientos -> desapilar();
	
	if ((padreAHijo == 'i') && (abueloAPadre == 'i')){
		
		// Hijo izquierdo de un hijo izquierdo (ZIG-ZIG)
		rotarPadreADerechaDeHijo(abuelo, padre);
		rotarPadreADerechaDeHijo(padre, hijo);
		
	} else if ((padreAHijo == 'd') && (abueloAPadre == 'd')) {
			
			// Hijo derecho de un hijo derecho (ZIG-ZIG)
			rotarPadreAIzquierdaDeHijo(abuelo, padre);
			rotarPadreAIzquierdaDeHijo(padre, hijo);
		
		} else if ((padreAHijo == 'i') && (abueloAPadre == 'd')) {
			
				// Hijo izquierdo de un hijo derecho (ZIG-ZAG)
				rotarPadreADerechaYAbueloAIzquierdaDelHijo(abuelo, padre, hijo);
				rotarPadreAIzquierdaDeHijo(abuelo, hijo);
				
			} else if ((padreAHijo == 'd') && (abueloAPadre == 'i')) {
				
						// Hijo derecho de un hijo izquierdo (ZIG-ZAG)
						rotarPadreAIzquierdaYAbueloADerechaDelHijo(abuelo, padre, hijo);
						rotarPadreADerechaDeHijo(abuelo, hijo);
						
					}
					
	// Vuelvo a poner al hijo en la pila.
	// La raiz vuelve a ser el hijo en las siguientes rotaciones.
	// De este modo llega a ser la raiz.
	nodos -> apilar(hijo);
	
};

void rotacionSimple(Pila<Nodo*>* nodos, Pila<char>* movimientos){
	
	// Dos nodos a rotar.
	Nodo* hijo = nodos -> desapilar();
	Nodo* padre = nodos -> desapilar();
	
	// Movimientos.
	char padreAHijo = movimientos -> desapilar();
	
		if (padreAHijo == 'd'){
		
		// Hijo derecho (ZIG)
		rotarPadreAIzquierdaDeHijo(padre, hijo);
		
	} else if (padreAHijo == 'i'){
			
			// Hijo izquierdo (ZIG)
			rotarPadreADerechaDeHijo(padre, hijo);
		
		}
	
};
	
// 1
void rotarPadreADerechaDeHijo(Nodo* nodoPadre, Nodo* nodoHijo){
	
	int auxiliar = nodoHijo -> getNumeroDeBloqueHijoDerecho();
	nodoHijo -> setNumeroDeBloqueHijoDerecho(nodoPadre -> getNumeroDeBloque());
	nodoPadre -> setNumeroDeBloqueHijoIzquierdo(auxiliar);
	
};
// 2
void rotarPadreAIzquierdaDeHijo(Nodo* nodoPadre, Nodo* nodoHijo){
	
	int auxiliar = nodoHijo -> getNumeroDeBloqueHijoIzquierdo();
	nodoHijo -> setNumeroDeBloqueHijoIzquierdo(nodoPadre -> getNumeroDeBloque());
	nodoPadre -> setNumeroDeBloqueHijoDerecho(auxiliar);
	
};
//3
void rotarPadreAIzquierdaYAbueloADerechaDelHijo(Nodo* nodoAbuelo, Nodo* nodoPadre, Nodo* nodoHijo){
	
	rotarPadreAIzquierdaDeHijo(nodoPadre, nodoHijo);
	nodoAbuelo -> setNumeroDeBloqueHijoIzquierdo(nodoHijo -> getNumeroDeBloque());
	
};
//4
void rotarPadreADerechaYAbueloAIzquierdaDelHijo(Nodo* nodoAbuelo, Nodo* nodoPadre, Nodo* nodoHijo){
	
	rotarPadreADerechaDeHijo(nodoPadre, nodoHijo);
	nodoAbuelo -> setNumeroDeBloqueHijoDerecho(nodoHijo -> getNumeroDeBloque());
	
};
