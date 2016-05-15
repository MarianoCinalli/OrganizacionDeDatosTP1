#include "Nodo.h"

class Nodo{

	// Atributos
	private:
		int numeroDeBloqueHijoIzquierdo;
		int numeroDeBloqueHijoDerecho;
		Nodo* hijoIzquierdo;
		Nodo* hijoDerecho;
		Lista<Registro>* registros;

	// Metodos

	public:
		Nodo();

		void setNumeroDeBloqueHijoIzquierdo(int numero);
		int getNumeroDeBloqueHijoIzquierdo();

		void setNumeroDeBloqueHijoDerecho(int numero);
		int getNumeroDeBloqueHijoDerecho();

		void setHijoIzquierdo(Nodo* hijoIzquierdo);
		Nodo* getHijoIzquierdo();

		void setHijoDerecho(Nodo* hijoDerecho);
		Nodo* getHijoDerecho();
		
		int getMenorClave();
		int getMayorClave();
		
		Lista<Registro>* getListaDeRegistros();
		
		~Nodo();
};
