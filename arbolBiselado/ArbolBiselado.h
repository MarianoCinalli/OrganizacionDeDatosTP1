#ifndef _ARBOLBISELADO_H
#define _ARBOLBISELADO_H
#include "utilidadesDelArbol/Nodo.h"
class ArbolBiselado{

	// Atributos


	private:
		Nodo* raiz;

	// Metodos
	public:
		ArbolBiselado();

		void insertar(Registro* registro);
		void modificar(Registro* registro);
		void eliminar(int identificador);

		~ArbolBiselado();
};

#endif // ARBOLBISELADO_H
