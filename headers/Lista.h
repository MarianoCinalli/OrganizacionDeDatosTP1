#include "NodoSimplementeEnlasado.h"

#ifndef _LISTA_H
#define _LISTA_H


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

	private:
            NodoSimplementeEnlasado<T>* obtenerNodo(unsigned int posicion);

};

// Implementacion de metodos

template <class T> Lista<T>::Lista(){
}
	
template <class T> unsigned int Lista<T>::getTamanio(){
}
	
template <class T> bool Lista<T>::estaVacia(){
}

template <class T> void Lista<T>::agregar(T elemento){
}
	
template <class T> void Lista<T>::remover(unsigned int posicion){
}

template <class T> void Lista<T>::iniciarCursor(){
}
	
template <class T> bool Lista<T>::avanzarCursor(){
	return true;
}

template <class T> T Lista<T>::obtenerCursor(){
}

template <class T> NodoSimplementeEnlasado<T>* Lista<T>::obtenerNodo(unsigned int posicion){
}

#endif // LISTA_H

