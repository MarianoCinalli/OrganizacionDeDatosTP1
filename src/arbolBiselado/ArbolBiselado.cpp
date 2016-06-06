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

        bool resultado = true;
		resultado = modificarRecursivo(raiz,registroAModificar);

		Pila<Nodo*>* nodosAliberar = biselar(this -> nodosARotar ,this -> movimientos, this -> raiz);
		//liberarMemoria(this -> registrosProcesados);
        return resultado;
	};

	bool ArbolBiselado::eliminar(Registro* registroAEliminar)
	{
	     bool resultado = true;
         resultado = eliminarRecursivo(raiz,registroAEliminar);
         Pila<Nodo*>* nodosAliberar = biselar(this -> nodosARotar ,this -> movimientos, this -> raiz);
         //liberarMemoria(this -> registrosProcesados);
         return resultado;
	};
	void ArbolBiselado::desapilarSiNodoQuedaVacio(Nodo* nodoActual)
	{
	    //se invoca la funcion justo antes de eliminar el
	    //ultimo registro, por eso pregunto por 1 y no por 0.
	    Nodo* nodoVacio;
	    if(nodoActual->getListaDeRegistros()->getTamanio() == 1)
        {
            nodoVacio = nodosARotar->desapilar();
        }
	}
	bool ArbolBiselado::eliminarRecursivo(Nodo* nodoActual, Registro* registroAEliminar)
	{
	    int posicionRegistro = 0;
	    nodosARotar->apilar(nodoActual);
        if(nodoActual->esHoja())
        {
            desapilarSiNodoQuedaVacio(nodoActual);
            eliminarEnHoja(registroAEliminar,nodoActual);
        }
        else if(nodoActual->esElMayor(registroAEliminar))
        {
            movimientos->apilar('d');
            avanzarAlHijoDerecho(registroAEliminar,nodoActual);
            eliminarRecursivo(nodoActual->getHijoDerecho(),registroAEliminar);
        }
        else if(nodoActual->esElMenor(registroAEliminar))
        {
            movimientos->apilar('i');
            avanzarAlHijoIzquierdo(registroAEliminar,nodoActual);
            eliminarRecursivo(nodoActual->getHijoIzquierdo(),registroAEliminar);
        }
        else
        {
            if(!nodoActual->encontrarRegistro(registroAEliminar,posicionRegistro))
            {
                cout << "El registro con el ID ingresado no se encuentra en el árbol." << endl;
                return false;
            }
            else
            {
                eliminarEnNodoInterno(registroAEliminar,nodoActual);
            }
        }
	}
void ArbolBiselado::eliminarEnNodoInterno(Registro* registroAEliminar,Nodo* nodo)
{
    //es decir, si no queda vacio el nodo
    if(nodo->getListaDeRegistros()->getTamanio() > 1)
    {
        nodo->eliminarRegistro(registroAEliminar);
    }
    //Si queda vacio hay que agregarle el menor de los mayores
    else
    {
        //en este punto ya se que el nodo tiene hijo derecho, porque sino
        //seria una hoja
        //vale aclarar que por como hicimos la particion de nodos, cada nodo interno
        //tiene dos hijos, asi que siempre se podra conseguir el derecho
        Nodo* hijoDerecho = nodo->getHijoDerecho();
        nodosARotar->apilar(hijoDerecho);
        movimientos->apilar('d');
        //Elimino el registro
        nodo->eliminarRegistro(registroAEliminar);
        //Busco el nodo donde esta el registro menor de los mayores
        Nodo* menorDeLosMayores = obtenerMenorDeLosMayores(hijoDerecho);
        menorDeLosMayores->getListaDeRegistros()->iniciarCursor();
        menorDeLosMayores->getListaDeRegistros()->avanzarCursor();
        //Inserto tal registro en el nodo interno que quedo vacio
        insetarEnNodoInterno(menorDeLosMayores->getListaDeRegistros()->obtenerCursor(),nodo);
        //En caso de que el nodo hoja que contenia el registro sustituto
        //haya quedado vacio, lo desapilo para el biselado y elimino la duplicacion
        desapilarSiNodoQuedaVacio(menorDeLosMayores);
        eliminarEnHoja(menorDeLosMayores->getListaDeRegistros()->obtenerCursor(),menorDeLosMayores);
    }
}

Nodo* ArbolBiselado::obtenerMenorDeLosMayores(Nodo* nodo)
{
    Nodo* nodoActual = nodo;
    while(nodoActual->getHijoIzquierdo() != NULL)
    {
        nodoActual = nodoActual->getHijoIzquierdo();
        nodosARotar->apilar(nodoActual);
        movimientos->apilar('i');
    }
    return nodoActual;
}

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
		nodosARotar->apilar(nodoActual);
		if (nodoActual -> esElMenor(registroAModificar))
        {
            movimientos->apilar('i');
            avanzarAlHijoIzquierdo(registroAModificar,nodoActual);
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}

		if(nodoActual-> esElMayor(registroAModificar))
        {
            movimientos->apilar('d');
            avanzarAlHijoDerecho(registroAModificar,nodoActual);
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
            if(nodoActual->esHoja())
            {
                eliminarEnHoja(registroAModificar,nodoActual);
                insertarEnHoja(registroAModificar,nodoActual);
            }
            //sino es hoja es nodo interno
            else
            {
                eliminarEnNodoInterno(registroAModificar,nodoActual);
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
                        insertarRecursivo(registro ,nodo->getHijoDerecho());

					} else if ( nodo -> esElMenor(registro) ){

							this -> movimientos -> apilar('i');
							avanzarAlHijoIzquierdo(registro ,nodo);
                            insertarRecursivo(registro ,nodo->getHijoIzquierdo());

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

	};
    void ArbolBiselado::eliminarEnHoja(Registro* registro, Nodo* nodo)
    {
        nodo->eliminarRegistro(registro);
    }
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
