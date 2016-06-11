#include "NodoSimplementeEnlasado.h"
#include <cstddef>
#include <iostream>
#ifndef _LISTA_H
#define _LISTA_H
using namespace std;

// La lista va a tener que dejar de ser generica, para que el agregar pueda ser un agregar ordenado.
template <class T>
class Lista{

	// Atributos
	private:
		unsigned int tamanio;
		NodoSimplementeEnlasado<T>* primerElemento;
		NodoSimplementeEnlasado<T>* cursor;

	// Metodos
	public:
        	Lista();
        	unsigned int getTamanio();
        	bool estaVacia();

        	void agregar(T elemento);
        	void remover(unsigned int posicion);

        	void iniciarCursor();
        	bool avanzarCursor();

        	T obtenerCursor();
        	T obtenerUltimo();

	private:
            NodoSimplementeEnlasado<T>* obtenerNodo(unsigned int posicion);

};

// Implementacion de metodos

template <class T> Lista<T>::Lista(){
    this->primerElemento = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

template <class T> unsigned int Lista<T>::getTamanio(){

	return ( this-> tamanio );

}

template <class T> bool Lista<T>::estaVacia(){

	return ( this-> tamanio == 0 );

}

template <class T> void Lista<T>::agregar(T elemento){

    NodoSimplementeEnlasado<T>* nuevoElemento = new NodoSimplementeEnlasado<T>(elemento);
    //agrega ordenado siempre de menor a mayor
    int posicion = 1;
    if(tamanio == 0){
        primerElemento = nuevoElemento;
    } else if(tamanio == 1) {

         if(primerElemento->getDato() > elemento){

            NodoSimplementeEnlasado<T>* primeroViejo = primerElemento;
            primerElemento = nuevoElemento;
            nuevoElemento->setSiguiente(primeroViejo);

         }else{

             primerElemento->setSiguiente(nuevoElemento);

         }

    } else {
        bool insertado = false;
        while(!insertado & posicion < tamanio){

            NodoSimplementeEnlasado<T>* primero = obtenerNodo(posicion);
            NodoSimplementeEnlasado<T>* segundo = obtenerNodo(posicion+1);

            if(primero->getDato() <= elemento && segundo->getDato() >= elemento){

                primero->setSiguiente(nuevoElemento);
                nuevoElemento->setSiguiente(segundo);
                insertado = true;

            } else {

                if(primero->getDato() >= elemento && segundo->getDato() >= elemento ){

                   primerElemento = nuevoElemento;
                   primerElemento->setSiguiente(primero);
                   insertado = true;

                }
            }
            posicion++;
        }
    }
    if(posicion == tamanio)
    {
        //significa que va al final
        obtenerNodo(tamanio)->setSiguiente(nuevoElemento);
    }
    tamanio++;
}

template <class T> void Lista<T>::remover(unsigned int posicion){

      if ((posicion > 0) && (posicion <= this->tamanio)){

        NodoSimplementeEnlasado<T>* removido;

        if (posicion == 1) {

            removido = this->primerElemento;
            this->primerElemento = removido->getSiguiente();

        } else {

            NodoSimplementeEnlasado<T>* anterior = this->obtenerNodo(posicion - 1);
            removido = anterior->getSiguiente();
            anterior->setSiguiente(removido->getSiguiente());
        }

        delete removido;
        this->tamanio--;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();
    }

}
//ojo que al iniciar el cursor el puntero no se posiciona en el primer elemento
//hay que avanzar y ahi si estas posicionado en el primero.
template <class T> void Lista<T>::iniciarCursor(){

	cursor = 0;

}

// Cambia el cursor al elemento siguiente.
// Devuelve verdadero si el contador de elementos no supero el tamanio.
// Lo ultimo es para no preguntar por nulo.
template <class T> bool Lista<T>::avanzarCursor(){
	  if (this->cursor == 0) {
        this->cursor = this->primerElemento;

    } else {
        this->cursor = this->cursor->getSiguiente();
    }
    /* pudo avanzar si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}

template <class T> T Lista<T>::obtenerCursor(){

    T elemento;

    if (this->cursor != NULL) {

        elemento = this->cursor->getDato();
    }

    return elemento;

}

// 1<=posicion<=tamanio
template <class T> NodoSimplementeEnlasado<T>* Lista<T>::obtenerNodo(unsigned int posicion){

    NodoSimplementeEnlasado<T>* actual = this-> primerElemento;
    for (unsigned int i = 1; i < posicion; i++) {

        actual = actual->getSiguiente();
    }

    return actual;
}

template <class T> T Lista<T>::obtenerUltimo(){

    return obtenerNodo(tamanio-1)->getDato();

}


#endif // LISTA_H

