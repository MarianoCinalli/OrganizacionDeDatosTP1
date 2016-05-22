#ifndef _PILA_H
#define _PILA_H
#include "NodoSimplementeEnlasado.h"

template <class T>
class Pila{

	// Atributos
	private:
		unsigned int tamanio;
		NodoSimplementeEnlasado<T>* tope;

	// Metodos
	public:
		Pila();

		unsigned int getTamanio();
		bool estaVacia();
		T desapilar();
		void apilar(T elemento);

		~Pila();

};


// Implementacion de metodos -----------------------------------------------------------------------

template <class T> Pila<T>::Pila(){
}

template <class T> unsigned int Pila<T>::getTamanio(){
}

template <class T> bool Pila<T>::estaVacia(){
}

template <class T> T Pila<T>::desapilar(){
}

template <class T> void Pila<T>::apilar(T elemento){
}

template <class T> Pila<T>::~Pila(){
}

#endif // PILA_H
