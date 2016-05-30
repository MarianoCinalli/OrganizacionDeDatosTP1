#ifndef NODOSIMPLEMENTEENLASADO_H
#define NODOSIMPLEMENTEENLASADO_H

template <class T>

// Falta hacer el override del operador de igualdad y desigualdad.

class NodoSimplementeEnlasado{

	// Atributos
    	private:
    		T dato;
        	NodoSimplementeEnlasado<T>* siguiente;

	// Metodos
	public:
        	NodoSimplementeEnlasado(T nuevoDato);
       		T getDato();
        	void setDato( T nuevoDato);
        	NodoSimplementeEnlasado <T> * getSiguiente();
        	void setSiguiente(NodoSimplementeEnlasado <T> * nuevoSiguiente);

};

// Implementacion de metodos --------------------------------------------------------------------------

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

#endif // NODOSIMPLEMENTEENLASADO_H
