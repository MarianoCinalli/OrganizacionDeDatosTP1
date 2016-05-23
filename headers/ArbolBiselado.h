#include "Nodo.h"
#include "funcionesDeBiselado.h"
#include "Lista.h"
#include "Registro.h"

#ifndef _ARBOLBISELADO_H
#define _ARBOLBISELADO_H

class ArbolBiselado{

	// Atributos


	private:
		Nodo* raiz;

	// Metodos
	public:
		ArbolBiselado();

		void insertar(Registro* registro);
		bool modificar(Registro* registroAModificar);
		void eliminar(int identificador);

		~ArbolBiselado();

	private:
		
		bool modificarRecursivo(Nodo* nodoActual, Registro* registro);
        
        bool encontrarRegistroEnNodo(Nodo* nodoActual, Registro* registroModificado, int& posicionDeRegistro);
        
        void insertarRecursivo(Registro* registro, Nodo* nodo);
        
};

#endif // ARBOLBISELADO_H
