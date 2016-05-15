#include "Lista.h"
#include "NodoSimplementeEnlasado.h"

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
