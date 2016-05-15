#include "Pila.h"

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
		// Devuelve un registro
		T desapilar();
		void apilar(T elemento);

		~Pila();
};
