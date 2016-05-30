#include "Pila.h"
#include "Nodo.h"

#ifndef FUNCIONESDEBISELADO_INCLUDED
#define FUNCIONESDEBISELADO_INCLUDED

// Funcion publica.

void biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos, Nodo* raiz );

// Funciones internas privadas.

void rotacionDoble(Pila<Nodo*>* nodos, Pila<char>* movimientos);

void rotacionSimple(Pila<Nodo*>* nodos, Pila<char>* movimientos);

void rotarPadreADerechaDeHijo(Nodo* nodoPadre, Nodo* nodoHijo);

void rotarPadreAIzquierdaDeHijo(Nodo* nodoPadre, Nodo* nodoHijo);

void rotarPadreAIzquierdaYAbueloADerechaDelHijo(Nodo* nodoAbuelo, Nodo* nodoPadre, Nodo* nodoHijo);

void rotarPadreADerechaYAbueloAIzquierdaDelHijo(Nodo* nodoAbuelo, Nodo* nodoPadre, Nodo* nodoHijo);

#endif // FUNCIONESDEBISELADO_INCLUDED
