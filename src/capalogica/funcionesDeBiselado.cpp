#include "funcionesDeBiselado.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Pila.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/Nodo.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/funcionesDeBiselado.h"

// 9 de cada 10 doctores recomiendan ver la documentacion,
// para entender como funciona esto.

// Toma una pila de nodos y, segun los movimientos, los rota.
// Al final devuelve la nueva raiz y las pilas de movimientos y nodos vuelven vacias.
Nodo* biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos ){
	int cantidadDeNodos = nodos -> getTamanio();
	// Esto es para un procesamiento posterior
	// No importa en las rotaciones, ignorar.
	Pila<Nodo*>*  nodosProcesados = new Pila<Nodo*>;

	// ¿Como funciona?
	// Tengo que llevar el ultimo nodo procesado, el ultimo de la pila, a la raiz.
	// Para ello roto los nodos hasta que el unico elemento restante el la pila sea la nueva raiz.
	while ( cantidadDeNodos != 1 ){
		
		if (cantidadDeNodos >= 3){
			// Si hay tres o mas nodos tengo que rotar de a tres.
			rotacionDoble(nodos, movimientos, nodosProcesados);

		} else {
			// Si hay dos, el unico caso restante, se rotan esos dos.
			rotacionSimple(nodos, movimientos, nodosProcesados);

		}
		
		cantidadDeNodos = nodos -> getTamanio();

	}
	// Ahora queda solo un nodo en la pila, el cual es la nueva raiz.
	
	return nodos -> desapilar();

}

// Funciones internas, privadas. ---------------------------------------

void rotacionDoble(Pila<Nodo*>* nodos, Pila<char>* movimientos, Pila<Nodo*>*  nodosProcesados){

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
	// Apilo el padre y al abuelo para luego persistir y liberar memoria.
	//nodosProcesados -> apilar(padre);
	//nodosProcesados -> apilar(abuelo);
	delete padre;
	delete abuelo;

};

void rotacionSimple(Pila<Nodo*>* nodos, Pila<char>* movimientos, Pila<Nodo*>*  nodosProcesados){
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

	// Vuelvo a poner al hijo en la pila.
	// La raiz vuelve a ser el hijo en las siguientes rotaciones.
	// De este modo llega a ser la raiz.
	nodos -> apilar(hijo);
	
	delete padre;

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
