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
		Nodo(int hijoDerecho, Lista<Registro*>* listaDeRegistros, int hijoIzquierdo, int numeroDeBloque, bool esHoja);

		void setNumeroDeBloqueHijoIzquierdo(int numero);
		int getNumeroDeBloqueHijoIzquierdo();

		void setNumeroDeBloqueHijoDerecho(int numero);
		int getNumeroDeBloqueHijoDerecho();

		Nodo* getHijoIzquierdo();
		Nodo* getHijoDerecho();

		int getNumeroDeBloque();
		void setNumeroDeBloque(int numeroDeBloque);

		bool esElMenor(Registro* registro);
		bool esElMayor(Registro* registro);
		bool estaIncluido(Registro* registro);
		bool esHoja();

		Lista<Registro*>* getListaDeRegistros();
		Lista<Registro*>* obtenerRegistrosMayoresA(Registro* registro);
		Lista<Registro*>* obtenerRegistrosMenoresA(Registro* registro);
		void agregarRegistro(Registro* nuevoRegistro);
		void eliminarRegistro(Registro* registroEliminable);
		bool encontrarRegistro(Registro* registroModificado,int& posicionDeRegistro);
		~Nodo();
		
	private:
	
		void borrarNodoVacio();
		
};

#endif // NODO_H
