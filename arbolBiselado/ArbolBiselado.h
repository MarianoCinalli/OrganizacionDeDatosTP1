#ifndef _ARBOLBISELADO_H
#define _ARBOLBISELADO_H
#include "utilidadesDelArbol/Nodo.h"
class ArbolBiselado{

	// Atributos


	private:
		Nodo* raiz;
        bool modificarRecursivo(Nodo* nodoActual, Registro* registro);
        bool encontrarRegistroEnNodo(Nodo* nodoActual, Registro* registroModificado, int& posicionDeRegistro);
	// Metodos
	public:
		ArbolBiselado();

		void insertar(Registro* registro);
		bool modificar(Registro* registroAModificar);
		void eliminar(int identificador);

		~ArbolBiselado();
};

#endif // ARBOLBISELADO_H
