#include "funcionesDeBiselado.h"
#include "funcionesDePersistencia.h"
#include "Nodo.h"
#include "Registro.h"
#include "Pila.h"
#include "Lista.h"
#include "excepciones/ElNodoExcedeElTamanioMaximo.h"
#include "excepciones/ElNodoNoTieneHijoEnEsaDireccion.h"

#ifndef _ARBOLBISELADO_H
#define _ARBOLBISELADO_H

class ArbolBiselado{

	// Atributos


	private:
		Nodo* raiz;
		Pila<Nodo*>* nodosARotar;
		Pila<char>* movimientos;

	// Metodos
	public:
		ArbolBiselado(Nodo* raiz);

		void insertar(Registro* registro);
		bool modificar(Registro* registroAModificar);
		bool eliminar(Registro* registroAEliminar);
		
		void liberarMemoria(Pila<Nodo*>* nodosAliberar);

		~ArbolBiselado();

	private:

		bool modificarRecursivo(Nodo* nodoActual, Registro* registro);
        bool eliminarRecursivo(Nodo* nodoActual, Registro* registro);
        void eliminarEnHoja(Registro* registro, Nodo* nodo);
        void avanzarALaDerecha(Registro* registro, Nodo* nodo);
		void avanzarALaIzquierda(Registro* registro, Nodo* nodo);

        void insertarRecursivo(Registro* registro, Nodo* nodo);
		void insertarEnSubArbolDerecho(Registro* registro ,Nodo* nodo);
		void insertarEnSubArbolIzquierdo(Registro* registro ,Nodo* nodo);
		void insertarEnHoja(Registro* registro ,Nodo* nodo);
        void insetarEnNodoInterno(Registro* registro ,Nodo* nodo);
        void insertarSinBiselar(Lista<Registro*>* registros, Nodo* nodo);
        void insetarSinBiselarRecursivo( Registro* registro, Nodo* nodo, Pila<Nodo*>* nodosALiberar );
        
        void desapilarSiNodoQuedaVacio(Nodo* nodoActual);
        void eliminarEnNodoInterno(Registro* registro, Nodo* nodo);
        Registro* obtenerMenorDeLosMayores(Nodo* nodo);
        Registro* obtenerMayorDeLosMenores(Nodo* nodo);
};

#endif // ARBOLBISELADO_H
