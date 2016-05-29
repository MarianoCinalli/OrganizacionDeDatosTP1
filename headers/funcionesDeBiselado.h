#include "Pila.h"
#include "Nodo.h"

#ifndef FUNCIONESDEBISELADO_INCLUDED
#define FUNCIONESDEBISELADO_INCLUDED

// Funcion publica.

void biselar( Pila<Nodo*>* nodos, Pila<char>* movimientos, Nodo* raiz );

// Funciones internas privadas.

void rotacionDoble(Pila<Nodo*>* nodos, Pila<char>* movimientos);

void rotacionTriple(Pila<Nodo*>* nodos, Pila<char>* movimientos);

#endif // FUNCIONESDEBISELADO_INCLUDED
