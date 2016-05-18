#include "NodoSimplementeEnlasado.h"

	// Metodos
		template <class T> NodoSimplementeEnlasado<T>::NodoSimplementeEnlasado (T nuevoDato){
    			this->dato = nuevoDato;
    			//this->siguiente = NULL;
		}

		template <class T> T NodoSimplementeEnlasado<T>::getDato(){
    			return this->dato;
		}

		template <class T> void NodoSimplementeEnlasado<T>::setDato(T nuevoDato){
    			this->dato = nuevoDato;
		}

		template <class T> NodoSimplementeEnlasado <T>* NodoSimplementeEnlasado<T>::getSiguiente(){
    			return this->siguiente;
		}

		template <class T> void NodoSimplementeEnlasado<T>::setSiguiente(NodoSimplementeEnlasado <T>* nuevoSiguiente){
    			this-> siguiente = nuevoSiguiente;
		}

