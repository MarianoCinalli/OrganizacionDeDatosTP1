#ifndef NODOSIMPLEMENTEENLASADO_H
#define NODOSIMPLEMENTEENLASADO_H

template <class T>

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

#endif // NODOSIMPLEMENTEENLASADO_H
