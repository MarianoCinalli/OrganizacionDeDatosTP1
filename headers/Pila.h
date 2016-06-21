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

template <class T> Pila<T>::Pila()
{
    tope = 0;
    tamanio = 0;
}

template <class T> unsigned int Pila<T>::getTamanio()
{
    return tamanio;
}

template <class T> bool Pila<T>::estaVacia()
{
    return (tope == 0);
}

template <class T> T Pila<T>::desapilar()
{
    NodoSimplementeEnlasado<T>* auxiliar = tope;
    tope = auxiliar->getSiguiente();
    T dato = auxiliar->getDato();
    tamanio--;
    delete auxiliar;
    return dato;
}

template <class T> void Pila<T>::apilar(T elemento){
	
    NodoSimplementeEnlasado<T>* nuevoTope = new NodoSimplementeEnlasado<T>(elemento);
    nuevoTope->setSiguiente(tope);
    tope = nuevoTope;
    tamanio++;
    
}

// No libera memoria.
template <class T> Pila<T>::~Pila(){
	
    while(!this->estaVacia()){
		
        desapilar();

    }
}

#endif // PILA_H
