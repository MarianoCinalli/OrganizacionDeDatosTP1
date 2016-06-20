#include "Lista.h"
#include "Registro.h"

#ifndef _NODO_H
#define _NODO_H

class Nodo{

	// Atributos
	private:

		unsigned int numeroDeBloqueHijoIzquierdo;
		unsigned int numeroDeBloqueHijoDerecho;
		unsigned int numeroDeBloque;
		Lista<Registro*>* registros;
		bool esNodoHoja;

	// Metodos
	public:
		Nodo();
		Nodo(Lista<Registro*>* registros);
		Nodo(unsigned int hijoDerecho, Lista<Registro*>* listaDeRegistros, unsigned int hijoIzquierdo, unsigned int numeroDeBloque, bool esHoja);

		void setNumeroDeBloqueHijoIzquierdo(unsigned int numero);
		unsigned int getNumeroDeBloqueHijoIzquierdo();

		void setNumeroDeBloqueHijoDerecho(unsigned int numero);
		unsigned int getNumeroDeBloqueHijoDerecho();

		Nodo* getHijoIzquierdo();
		Nodo* getHijoDerecho();

		unsigned int getNumeroDeBloque();
		void setNumeroDeBloque(unsigned int numeroDeBloque);

		bool esElMenor(Registro* registro);
		bool esElMayor(Registro* registro);
		bool estaIncluido(Registro* registro);
		bool esHoja();
		bool estaVacio();

		Lista<Registro*>* getListaDeRegistros();
		Lista<Registro*>* obtenerRegistrosMayoresA(Registro* registro);
		Lista<Registro*>* obtenerRegistrosMenoresA(Registro* registro);
		void agregarRegistro(Registro* nuevoRegistro);
		void eliminarRegistro(Registro* registroEliminable);
		void modificarRegistro( Registro* registro );
		bool encontrarRegistro(Registro* registroModificado,int& posicionDeRegistro);
		~Nodo();
		
	private:
	
		void remover( Registro* registroEliminable );

};

#endif // NODO_H
