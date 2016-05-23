#include "Lista.h"
#include "Registro.h"

#ifndef _NODO_H
#define _NODO_H

class Nodo{

	// Atributos
	private:
		int numeroDeBloqueHijoIzquierdo;
		int numeroDeBloqueHijoDerecho;
		Nodo* hijoIzquierdo;
		Nodo* hijoDerecho;
		Lista<Registro>* registros;
		bool esNodoHoja;

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
		
		bool esElMenor(Registro* registro);
		bool esElMayor(Registro* registro);
		bool estaIncluido(Registro* registro);
		bool esHoja();

		Lista<Registro>* getListaDeRegistros();

		~Nodo();
};

#endif // NODO_H
