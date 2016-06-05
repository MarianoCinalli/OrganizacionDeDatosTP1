#include "Nodo.h"
#include "funcionesDePersistencia.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\funcionesDePersistencia.h"
	// Metodos

	// Constructores
	Nodo::Nodo(){

		// Invocar a la capa fisica para que le asigne el numero de bloque.
		this -> numeroDeBloqueHijoIzquierdo = 0;
		this -> numeroDeBloqueHijoDerecho = 0;
		this -> registros = new Lista<Registro*>;
		this -> esNodoHoja = true;

	};

	Nodo::Nodo(Lista<Registro*>* registros){

		// Invocar a la capa fisica para que le asigne el numero de bloque.
		this -> numeroDeBloqueHijoIzquierdo = 0;
		this -> numeroDeBloqueHijoDerecho = 0;
		this -> registros = registros;
		this -> esNodoHoja = true;

	};

	// Operaciones con los hijos

	void Nodo::setNumeroDeBloqueHijoIzquierdo(int numero){

		this -> esNodoHoja = false;

	};

	int Nodo::getNumeroDeBloqueHijoIzquierdo(){
	};

	void Nodo::setNumeroDeBloqueHijoDerecho(int numero){

		this -> esNodoHoja = false;

	};

	int Nodo::getNumeroDeBloqueHijoDerecho(){
	};

	Nodo* Nodo::getHijoIzquierdo(){
	};

	Nodo* Nodo::getHijoDerecho(){
	};

	// Operaciones de informacion del nodo

	int Nodo::getNumeroDeBloque(){
	};

	bool Nodo::esHoja(){

	    return esNodoHoja;

	};

	// Operaciones con registros
	bool Nodo::esElMenor(Registro* registro){

	    registros-> iniciarCursor();
	    registros-> avanzarCursor();
	    Registro* primerRegistro = registros -> obtenerCursor();

	    return ( registro-> getCampoIndexante() < primerRegistro -> getCampoIndexante() );

	};

	bool Nodo::esElMayor(Registro* registro){

		registros-> iniciarCursor();
		Registro* ultimoRegistro = registros -> obtenerUltimo();

	    return ( registro-> getCampoIndexante() > ultimoRegistro -> getCampoIndexante() );

	};

	bool Nodo::estaIncluido(Registro* registro){
	};

	void Nodo::agregarRegistro(Registro* nuevoRegistro)	{
        registros->agregar(nuevoRegistro);
        //persistir(this); �Esto habia que incluir? Es funcion del ArbolBiselado
	};
    void Nodo::eliminarRegistro(Registro* registroEliminable){

        registros -> iniciarCursor();
        int posicion = 1;
        bool encontrado = false;

        while(registros->avanzarCursor() && !encontrado){

            if(registroEliminable->getCampoIndexante() != registros->obtenerCursor()->getCampoIndexante()){

                posicion++;
                encontrado = true;

            }

        }

        registros -> remover(posicion);
        //En el persistir se especifica la grabacion de modificar el bitmap
        //con un nodo vacio? (es decir cambiar su estado de ocupado a libre)
        persistir(this);
        borrarNodoVacio();
    };
    void Nodo::borrarNodoVacio()
    {
        if(registros->getTamanio() == 0)
        {
            delete this;
        }
    }
	Lista<Registro*>* Nodo::getListaDeRegistros(){

        return registros;

	};

	// Devuelve una lista de registros que son menores, en clave,
	// al registro pasado por parametro. Los elimina de la lista. �Cu�les elimina?
	Lista<Registro*>* Nodo::obtenerRegistrosMenoresA(Registro* registro){

        Lista<Registro*>* registrosMenores = new Lista<Registro*>;
        registros->iniciarCursor();
        int campoRegistroRecibido =  registro -> getCampoIndexante();
        int campoRegistroActual = registros-> obtenerCursor()-> getCampoIndexante();

        while( ( registros->avanzarCursor() ) && ( campoRegistroActual < campoRegistroRecibido ) ){

            registrosMenores->agregar(registros->obtenerCursor());
            campoRegistroActual = registros-> obtenerCursor()-> getCampoIndexante();

        }

        return registrosMenores;
	};

	// Devuelve una lista de registros que son mayores, en clave,
	// al registro pasado por parametro. Los elimina de la lista. �Cu�les registros?
	Lista<Registro*>* Nodo::obtenerRegistrosMayoresA(Registro* registro){

        Lista<Registro*>* registrosMayores = new Lista<Registro*>;
        registros->iniciarCursor();
        int campoRegistroRecibido =  registro -> getCampoIndexante();
        int campoRegistroActual = registros-> obtenerCursor()-> getCampoIndexante();

        while( ( registros->avanzarCursor() ) && ( campoRegistroActual > campoRegistroRecibido ) ){

            registrosMayores->agregar(registros->obtenerCursor());
            campoRegistroActual = registros-> obtenerCursor()-> getCampoIndexante();

        }

        return registrosMayores;
	};

    bool Nodo::encontrarRegistro(Registro* registroModificado,
                           int& posicionDeRegistro){

       this->getListaDeRegistros()->iniciarCursor();

       while(this->getListaDeRegistros()->avanzarCursor()){

            if(this->getListaDeRegistros()->obtenerCursor()->getCampoIndexante() == registroModificado->getCampoIndexante()){
                return true;
            }

            posicionDeRegistro++;
       }

       return false;
    }
	Nodo::~Nodo(){
	};
