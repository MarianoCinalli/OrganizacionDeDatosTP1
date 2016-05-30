#include "ArbolBiselado.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/ArbolBiselado.h"
// Metodos

	ArbolBiselado::ArbolBiselado(){
	};

	void ArbolBiselado::insertar(Registro* registro){

		insertarRecursivo( registro, this->raiz);

		Pila<Nodo*>* nodosAliberar = biselar(this -> nodosARotar ,this -> movimientos, this -> raiz);
		//liberarMemoria(nodosAliberar);

	};

	bool ArbolBiselado::modificar(Registro* registroAModificar){

		return modificarRecursivo(raiz,registroAModificar);

		Pila<Nodo*>* nodosAliberar = biselar(this -> nodosARotar ,this -> movimientos, this -> raiz);
		//liberarMemoria(this -> registrosProcesados);

	};

	void ArbolBiselado::eliminar(Registro* registroAEliminar){

	};
	/*
	bool ArbolBiselado::encontrarRegistroEnNodo(Nodo* nodoActual, Registro* registroModificado, int& posicionDeRegistro){

		nodoActual->getListaDeRegistros()->iniciarCursor();

		while(nodoActual->getListaDeRegistros()->avanzarCursor()){

			if(nodoActual->getListaDeRegistros()->obtenerCursor().getID() == registroModificado->getID()){
				return true;
			}
			posicionDeRegistro++;
       }

       return false;
     }
     */

	ArbolBiselado::~ArbolBiselado(){

		delete nodosARotar;
		delete movimientos;

	};

	// Metodos privados ------------------------------------------------

	bool ArbolBiselado::modificarRecursivo(Nodo* nodoActual, Registro* registroAModificar)
	{

		int posicionRegistro = 0;
		// Te cambie los metodos de los if's por los que van.
		// Creo que necesitas ponerle else a los if's para no evaluar al pedo.
		if (nodoActual -> esElMenor(registroAModificar))
        {
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}

		if(nodoActual-> esElMayor(registroAModificar))
        {
			modificarRecursivo(nodoActual->getHijoDerecho(),registroAModificar);
		}

        if(!nodoActual->encontrarRegistro(registroAModificar,posicionRegistro))
        {
            cout << "El registro con el ID ingresado no se encuentra en el árbol." << endl;
            //biselar();
            return false;
        }
        else
        {
            nodoActual->eliminarRegistro(registroAModificar);
            //eliminar(registroAModificar); seria lo correcto
            if(nodoActual->esHoja())
            {
                insertarEnHoja(registroAModificar,nodoActual);
            }
            //sino es hoja es nodo interno
            else
            {
                insetarEnNodoInterno(registroAModificar,nodoActual);
            }
            return true;
        }
    };

	// Funciones de insertar ---------------------------------------------------

	void ArbolBiselado::insertarRecursivo( Registro* registro, Nodo* nodo){

			this -> nodosARotar -> apilar(nodo);

			if (nodo -> estaIncluido(registro)){

				// Excepcion
				// throw elRegistroYaPerteneceAlArbol

			} else if (nodo -> esHoja()){

					insertarEnHoja(registro, nodo);

				} else if ( nodo -> esElMayor(registro) ){

						this -> movimientos -> apilar('d');
						avanzarAlHijoDerecho(registro ,nodo);

					} else if ( nodo -> esElMenor(registro) ){

							this -> movimientos -> apilar('i');
							avanzarAlHijoIzquierdo(registro ,nodo);

						} else {

								this -> insetarEnNodoInterno(registro, nodo);

							}

		};

	void ArbolBiselado::avanzarAlHijoDerecho(Registro* registro ,Nodo* nodo){

		Nodo* hijoDerecho;

		try {

			hijoDerecho = nodo -> getHijoDerecho();

		} catch ( ElNodoNoTieneHijoEnEsaDireccion e) {

			// Creo el nuevo nodo.
			hijoDerecho = new Nodo();
			// Actualizo el numero de bloque.
			nodo -> setNumeroDeBloqueHijoDerecho( hijoDerecho -> getNumeroDeBloque() );
			// Persisto los cambios.
			persistir(nodo);
			persistir(hijoDerecho);

		}

			insertarRecursivo(registro ,hijoDerecho);

	};

	void ArbolBiselado::avanzarAlHijoIzquierdo(Registro* registro ,Nodo* nodo){

		Nodo* hijoIzquierdo;

		try {

			hijoIzquierdo = nodo -> getHijoIzquierdo();

		} catch ( ElNodoNoTieneHijoEnEsaDireccion e) {

			// Creo el nuevo nodo.
			hijoIzquierdo = new Nodo();
			// Actualizo el numero de bloque.
			nodo -> setNumeroDeBloqueHijoIzquierdo( hijoIzquierdo -> getNumeroDeBloque() );
			// Persisto los cambios.
			persistir(nodo);
			persistir(hijoIzquierdo);

		}

		insertarRecursivo(registro ,hijoIzquierdo);

	};

	void ArbolBiselado::insertarEnHoja(Registro* registro ,Nodo* nodo){

		try {

			nodo -> agregarRegistro(registro);


		} catch ( ElNodoExcedeElTamanioMaximo e) {

			// Variables temporales.
			Nodo* hijoIzquierdo;
			Nodo* hijoDerecho;

			Lista<Registro*>* registrosHijoIzquierdo;
			Lista<Registro*>* registrosHijoDerecho;

			// Parto la lista.
			registrosHijoIzquierdo = nodo -> obtenerRegistrosMenoresA(registro);
			registrosHijoDerecho = nodo -> obtenerRegistrosMayoresA(registro);

			// Creo dos nodos nuevos con los registros.
			hijoIzquierdo = new Nodo(registrosHijoIzquierdo);
			hijoDerecho = new Nodo(registrosHijoDerecho);

			// Actualizo numeros de bloque.
			nodo -> setNumeroDeBloqueHijoIzquierdo ( hijoIzquierdo -> getNumeroDeBloque() );
			nodo -> setNumeroDeBloqueHijoDerecho ( hijoDerecho -> getNumeroDeBloque() );

			// Persisto los cambios.
			persistir(nodo);
			persistir(hijoIzquierdo);
			persistir(hijoDerecho);

		}
	};

	void ArbolBiselado::insetarEnNodoInterno(Registro* registro ,Nodo* nodo){

		try {

			nodo -> agregarRegistro(registro);


		} catch ( ElNodoExcedeElTamanioMaximo e) {

			// Variables temporales.
			Nodo* hijoIzquierdo;
			Nodo* hijoDerecho;

			Lista<Registro*>* registrosHijoIzquierdo;
			Lista<Registro*>* registrosHijoDerecho;

			// Parto la lista.
			registrosHijoIzquierdo = nodo -> obtenerRegistrosMenoresA(registro);
			registrosHijoDerecho = nodo -> obtenerRegistrosMayoresA(registro);

			// Obtengo los hijos
			hijoIzquierdo = nodo -> getHijoIzquierdo();
			hijoDerecho = nodo -> getHijoDerecho();

			// Persisto los cambios.
			persistir(nodo);

			// Inserto los registros menores al nuevo.
			insertarSinBiselar(registrosHijoIzquierdo, hijoIzquierdo);
			// Inserto los registros mayores al nuevo.
			insertarSinBiselar(registrosHijoDerecho, hijoDerecho);

		}

	};

	void ArbolBiselado::insertarSinBiselar(Lista<Registro*>* registros, Nodo* nodo){

		Pila<Nodo*>* nodosALiberar = new Pila<Nodo*>;

		while (registros -> avanzarCursor()){

			insetarSinBiselarRecursivo(registros -> obtenerCursor(), nodo, nodosALiberar);

		}

		//liberarMemoria(nodosALiberar);
		delete nodosALiberar;

	};

	void ArbolBiselado::insetarSinBiselarRecursivo( Registro* registro, Nodo* nodo, Pila<Nodo*>* nodosALiberar ){

		nodosALiberar -> apilar(nodo);

		if (nodo -> esHoja()){

			insertarEnHoja(registro, nodo);

		} else if ( nodo -> esElMayor(registro) ){

				avanzarAlHijoDerecho(registro ,nodo);

			} else if ( nodo -> esElMenor(registro)){

					avanzarAlHijoIzquierdo(registro ,nodo);

				} else {

						insetarEnNodoInterno(registro, nodo);

					}
	};
