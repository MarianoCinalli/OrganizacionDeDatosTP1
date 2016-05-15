#include "NodoSimplementeEnlasado.h"

template <class T>
class NodoSimplementeEnlasado{

	// Atributos
    	private:
    		T dato;
        	NodoSimplementeEnlasado<T>* siguiente;

	// Metodos
	public:
		NodoSimplementeEnlasado (T nuevoDato){
    			this->dato = nuevoDato;
    			this->siguiente = NULL;
		}

		T getDato(){
    			return this->dato;
		}

		void setDato(T nuevoDato){
    			this->dato = nuevoDato;
		}

		NodoSimplementeEnlasado <T>* getSiguiente(){
    			return this->siguiente;
		}

		void setSiguiente(NodoSimplementeEnlasado <T>* nuevoSiguiente){
    			this-> siguiente = nuevoSiguiente;
		}

};
