#include "ArbolBiselado.h"
//#include "C:/CSV/TpDatos/OrganizacionDeDatosTP1/headers/ArbolBiselado.h"
// Metodos

ArbolBiselado::ArbolBiselado(Nodo* raiz){

    this -> raiz = raiz;
    this -> nodosARotar = new Pila<Nodo*>;
    this -> movimientos = new Pila<char>;

};

void ArbolBiselado::insertar(Registro* registro){

	insertarRecursivo( registro, this->raiz);
	this -> raiz = biselar(this -> nodosARotar ,this -> movimientos);

};

bool ArbolBiselado::modificar(Registro* registroAModificar){

	bool resultado = true;
	resultado = modificarRecursivo(raiz,registroAModificar);
	this -> raiz = biselar(this -> nodosARotar ,this -> movimientos);
	return resultado;
};

bool ArbolBiselado::eliminar(Registro* registroAEliminar){

     bool resultado = true;
     eliminarRecursivo(raiz,registroAEliminar);
	 this -> raiz = biselar(this -> nodosARotar ,this -> movimientos);
	 return resultado;

};

ArbolBiselado::~ArbolBiselado(){

	persistirRaiz(raiz);

	delete nodosARotar;
	delete movimientos;
	delete raiz;

};
// Metodos privados ----------------------------------------------------

// Metodos de eliminar -------------------------------------------------

bool ArbolBiselado::eliminarRecursivo(Nodo* nodoActual, Registro* registroAEliminar){

    int posicionRegistro = 0;
    nodosARotar->apilar(nodoActual);
	if(!nodoActual->encontrarRegistro(registroAEliminar,posicionRegistro))	{

		if(nodoActual->esElMayor(registroAEliminar)){

			movimientos->apilar('d');
			avanzarALaDerecha(registroAEliminar,nodoActual);
			eliminarRecursivo(nodoActual->getHijoDerecho(),registroAEliminar);

		} else if(nodoActual->esElMenor(registroAEliminar)) {

				movimientos->apilar('i');
				avanzarALaIzquierda(registroAEliminar,nodoActual);
				eliminarRecursivo(nodoActual->getHijoIzquierdo(),registroAEliminar);

			}	else{

					cout << "El registro con el ID ingresado no se encuentra en el �rbol." << endl;
					return false;
		}

	} else{

		if(nodoActual->esHoja()) {

			desapilarSiNodoQuedaVacio(nodoActual);
			eliminarEnHoja(registroAEliminar,nodoActual);

		} else {
				eliminarEnNodoInterno(registroAEliminar,nodoActual);
			}
	}
    eliminarReferenciaHojaVacia(nodoActual);
}

void ArbolBiselado::eliminarReferenciaHojaVacia(Nodo* nodoActual)
{
    if(nodoActual->estaVacio() && nodoActual->esHoja())
    {
        Nodo* padreHuerfano = nodosARotar->desapilar();
        char movimiento = movimientos->desapilar();
        if(movimiento =='i')
        {
            padreHuerfano->setNumeroDeBloqueHijoIzquierdo(0);
        }
        else
        {
            padreHuerfano->setNumeroDeBloqueHijoDerecho(0);
        }
        nodosARotar->apilar(padreHuerfano);
        movimientos->apilar(movimiento);
        delete nodoActual;
    }
}


void ArbolBiselado::eliminarEnNodoInterno(Registro* registroAEliminar,Nodo* nodo){
//es decir, si no queda vacio el nodo
if(nodo->getListaDeRegistros()->getTamanio() > 1){

	nodo->eliminarRegistro(registroAEliminar);

}
//Si queda vacio hay que agregarle el menor de los mayores o el mayor de los menores
else
{
    try
	{
		Nodo* hijoDerecho = nodo->getHijoDerecho();
		nodosARotar->apilar(hijoDerecho);
		movimientos->apilar('d');
		//Busco el nodo donde esta el registro menor de los mayores
		Registro* menorDeLosMayores = obtenerMenorDeLosMayores(hijoDerecho);
		//Inserto tal registro en el nodo que quedaria vac�o
		//ahora el nodo queda con 2 registros: el que se eliminara y
		//el que se agrego para que no quede vacio
		nodo->getListaDeRegistros()->agregar(menorDeLosMayores);
		//Elimino el registro que se habia solicitado
		nodo->eliminarRegistro(registroAEliminar);
	}
	//En caso que no haya hijo derecho
	catch(NumeroDeBloqueInvalido e)
	{
		Nodo* hijoIzquierdo = nodo->getHijoIzquierdo();
		nodosARotar->apilar(hijoIzquierdo);
		movimientos->apilar('i');

		Registro* mayorDeLosMenores = obtenerMayorDeLosMenores(hijoIzquierdo);
		//Inserto tal registro en el nodo que quedaria vac�o
		//ahora el nodo queda con 2 registros: el que se eliminara y
		//el que se agrego para que no quede vacio
		nodo->getListaDeRegistros()->agregar(mayorDeLosMenores);
		//Elimino el registro
		nodo->eliminarRegistro(registroAEliminar);
	}
}
}

Registro* ArbolBiselado::obtenerMayorDeLosMenores(Nodo* nodo){

	Nodo* nodoActual = nodo;
	while(true)
    {
        try
        {
            nodoActual = nodoActual->getHijoDerecho();
        }
		catch(NumeroDeBloqueInvalido e)
		{
		    break;
		}
		nodosARotar->apilar(nodoActual);
		movimientos->apilar('d');

	}
	//En caso de que el nodo hoja que contenia el registro sustituto
	//haya quedado vacio, lo desapilo para el biselado y elimino la duplicacion
	desapilarSiNodoQuedaVacio(nodoActual);

	//obtengo el registro original a eliminar
	Registro* original = nodoActual->getListaDeRegistros()->obtenerUltimo();

	//duplico su informacion en el que se insertara en el nodo que quedo vacio
	Registro* duplicado = new Registro(original->getID(),original->getCodigo(), original->getDescripcion());

	//elimino el original si no es el unico registro restante o es hoja
	if(nodoActual->getListaDeRegistros()->getTamanio() > 1 || nodoActual->esHoja()){

		 nodoActual->eliminarRegistro(original);

	} else //en caso de que no (esta es la recursion) y el nodo prestador a su vez
		//queda vacio le aplico recursion para que busque otra vez el menor de los mayores
		//o mayor de los menores y repita todo el proceso, mejor dicho.
	{
		//fijate que en el unico caso que hay que hacer recursion
		//es si caemos en un nodo interno con un solo registro
		// (A || B) == �A && �B.
		eliminarEnNodoInterno(original,nodoActual);
	}

	return duplicado;

}

Registro* ArbolBiselado::obtenerMenorDeLosMayores(Nodo* nodo){
	Nodo* nodoActual = nodo;
	while(true)
	{
	    try
	    {
            nodoActual = nodoActual->getHijoIzquierdo();
	    }
	    catch(NumeroDeBloqueInvalido e)
	    {
	        break;
	    }
		nodosARotar->apilar(nodoActual);
		movimientos->apilar('i');
	}
	//En caso de que el nodo hoja que contenia el registro sustituto
	//haya quedado vacio, lo desapilo para el biselado y elimino la duplicacion
	desapilarSiNodoQuedaVacio(nodoActual);

	  //obtengo el registro original a eliminar
	nodoActual->getListaDeRegistros()->iniciarCursor();
	nodoActual->getListaDeRegistros()->avanzarCursor();
	Registro* original = nodoActual->getListaDeRegistros()->obtenerCursor();

	//duplico su informacion en el que se insertara en el nodo que quedo vacio
	Registro* duplicado = new Registro(original->getID(),original->getCodigo(), original->getDescripcion());

	if(nodoActual->getListaDeRegistros()->getTamanio() > 1
	   || nodoActual->esHoja())
	{
		 nodoActual->eliminarRegistro(original);
	}
	else //en caso de que no (esta es la recursion) y el nodo prestador a su vez
		//queda vacio le aplico recursion para que busque otra vez el menor de los mayores
		//o mayor de los menores y repita todo el proceso, mejor dicho.
	{
		//fijate que en el unico caso que hay que hacer recursion
		//es si caemos en un nodo interno con un solo registro
		// (A || B) == �A && �B.
		eliminarEnNodoInterno(original,nodoActual);
	}
	return duplicado;
}

void ArbolBiselado::desapilarSiNodoQuedaVacio(Nodo* nodoActual){

    //se invoca la funcion justo antes de eliminar el
    //ultimo registro, por eso pregunto por 1 y no por 0.
    Nodo* nodoVacio;
    char m;
    if(nodoActual-> getListaDeRegistros() ->getTamanio() == 1){

		nodoVacio = nodosARotar-> desapilar();
		m = movimientos->desapilar();

	}
}

void ArbolBiselado::avanzarALaDerecha(Registro* registro, Nodo* nodo){

	Nodo* hijoDerecho;

	try {

		hijoDerecho = nodo -> getHijoDerecho();

	} catch (NumeroDeBloqueInvalido e) {

	    cout << "El registro con el ID ingresado no se encuentra en el �rbol." << endl;

	}

}

void ArbolBiselado::avanzarALaIzquierda(Registro* registro, Nodo* nodo){

	Nodo* hijoIzquierdo;

	try {

		hijoIzquierdo = nodo -> getHijoIzquierdo();

	} catch (NumeroDeBloqueInvalido e) {

	    cout << "El registro con el ID ingresado no se encuentra en el �rbol." << endl;

	}

}

// Metodos de modificar ------------------------------------------------

bool ArbolBiselado::modificarRecursivo(Nodo* nodoActual, Registro* registroAModificar)
{

	int posicionRegistro = 0;
	// Te cambie los metodos de los if's por los que van.
	// Creo que necesitas ponerle else a los if's para no evaluar al pedo.
	nodosARotar->apilar(nodoActual);
	if(!nodoActual->encontrarRegistro(registroAModificar,posicionRegistro))
	{
		if (nodoActual -> esElMenor(registroAModificar))
		{
			movimientos->apilar('i');
			avanzarALaIzquierda(registroAModificar,nodoActual);
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}

		if(nodoActual-> esElMayor(registroAModificar))
		{
			movimientos->apilar('d');
			avanzarALaDerecha(registroAModificar,nodoActual);
			modificarRecursivo(nodoActual->getHijoDerecho(),registroAModificar);
		}
	}
	else
	{
	    nodoActual->modificarRegistro(registroAModificar);
		return true;
	}
};

void ArbolBiselado::eliminarEnHoja(Registro* registro, Nodo* nodo){
	nodo->eliminarRegistro(registro);
}

// Metodos de insertar ---------------------------------------------------

void ArbolBiselado::insertarRecursivo( Registro* registro, Nodo* nodo){

		this -> nodosARotar -> apilar(nodo);
		bool esMenor = nodo -> esElMenor(registro);
		bool esMayor = nodo -> esElMayor(registro);
		if (nodo -> estaIncluido(registro)){
                cout << "El nodo ya pertenece al �rbol." << endl;
			// Excepcion
			// throw elRegistroYaPerteneceAlArbol

		} else if (nodo -> esHoja()){
				this -> insertarEnHoja(registro, nodo);

			} else if ( !esMenor && !esMayor ){

					this -> insetarEnNodoInterno(registro, nodo);

				} else if ( esMenor ){

						this -> movimientos -> apilar('i');
						this -> insertarEnSubArbolIzquierdo(registro ,nodo);

					} else {

							this -> movimientos -> apilar('d');
							this -> insertarEnSubArbolDerecho(registro ,nodo);

						}

	};

void ArbolBiselado::insertarEnSubArbolDerecho(Registro* registro ,Nodo* nodo){

	Nodo* hijoDerecho;

	try {

		hijoDerecho = nodo -> getHijoDerecho();

	} catch ( NumeroDeBloqueInvalido e) {

		// Creo el nuevo nodo.
		hijoDerecho = new Nodo();
		// Actualizo el numero de bloque.
		nodo -> setNumeroDeBloqueHijoDerecho( hijoDerecho -> getNumeroDeBloque() );

	}

	insertarRecursivo(registro ,hijoDerecho);

};

void ArbolBiselado::insertarEnSubArbolIzquierdo(Registro* registro ,Nodo* nodo){

	Nodo* hijoIzquierdo;

	try {

		hijoIzquierdo = nodo -> getHijoIzquierdo();

	} catch ( NumeroDeBloqueInvalido e) {

		// Creo el nuevo nodo.
		hijoIzquierdo = new Nodo();
		// Actualizo el numero de bloque.
		nodo -> setNumeroDeBloqueHijoIzquierdo( hijoIzquierdo -> getNumeroDeBloque() );

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

	delete nodosALiberar;

};

void ArbolBiselado::insetarSinBiselarRecursivo( Registro* registro, Nodo* nodo, Pila<Nodo*>* nodosALiberar ){

	nodosALiberar -> apilar(nodo);
	bool esMenor = nodo -> esElMenor(registro);
	bool esMayor = nodo -> esElMayor(registro);

	if (nodo -> esHoja()){

			this -> insertarEnHoja(registro, nodo);

		} else if ( !esMenor && !esMayor ){

				this -> insetarEnNodoInterno(registro, nodo);

			} else if ( esMenor ){

					this -> insertarEnSubArbolIzquierdo(registro ,nodo);

				} else {

						this -> insertarEnSubArbolDerecho(registro ,nodo);

					}
};

