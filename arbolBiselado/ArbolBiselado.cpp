#include "ArbolBiselado.h"
#include "../funciones/biselado.h"
#include "../funciones/capaFisica.h"

class ArbolBiselado{

	// Atributos
	private:
		Nodo* raiz;
		// Faltan cosas aca, supongo que mientras programemos van a surgir.		

	// Metodos
	public:
		ArbolBiselado();
	
		void insertar(Registro* registro);
		void modificar(Registro* registro);
		void eliminar(int identificador);

		~ArbolBiselado();
};
