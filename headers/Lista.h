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
        void ordenar();
	// Metodos
	public:
        	Lista();
            ~Lista();
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
//Agrega elemento, el contenido esta ordenado de menor a mayor.
template <class T> void Lista<T>::agregar(T elemento){

    NodoSimplementeEnlasado<T>* nuevoElemento = new NodoSimplementeEnlasado<T>(elemento);
   tamanio++;
    if(tamanio > 1)
    {
        obtenerNodo(tamanio-1)->setSiguiente(nuevoElemento);
        ordenar();
    }
    else
    {
        primerElemento = nuevoElemento;
    }
    // Ahora podes hacer nuevoElemento < primerElemento
    // Te deje un ejemplo abajo.
    // No necesitas usar el getDato

}


template <class T> void Lista<T>::ordenar()
{

    NodoSimplementeEnlasado<T> dumy_node(0);
    NodoSimplementeEnlasado<T>* cur_node = primerElemento;

    while (cur_node)
    {
        NodoSimplementeEnlasado<T>* insert_cur_pos =  dumy_node.getSiguiente();
        NodoSimplementeEnlasado<T>* insert_pre_pos = NULL;

        while (insert_cur_pos)
        {
            if (*insert_cur_pos > *cur_node)
                break;

            insert_pre_pos = insert_cur_pos;
            insert_cur_pos = insert_cur_pos->getSiguiente();
        }

        if (!insert_pre_pos)
            insert_pre_pos = &dumy_node;

        NodoSimplementeEnlasado<T>* temp_node = cur_node->getSiguiente();

        cur_node->setSiguiente(insert_pre_pos->getSiguiente());
        insert_pre_pos->setSiguiente(cur_node);

        cur_node = temp_node;
    }
    primerElemento= dumy_node.getSiguiente();
}


template<class T> Lista<T>::~Lista() {

    while (this->primerElemento != 0) {

        NodoSimplementeEnlasado<T>* aBorrar = this->primerElemento;
        this->primerElemento = this->primerElemento->getSiguiente();

        delete aBorrar;
    }
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

