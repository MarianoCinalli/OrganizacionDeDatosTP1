#ifndef _PILA_H
#define _PILA_H

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

#endif // PILA_H
