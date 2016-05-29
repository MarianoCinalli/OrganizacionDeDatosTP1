#include "Nodo.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
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
	};

	// Operaciones con registros
	bool Nodo::esElMenor(Registro* registro){
	};

	bool Nodo::esElMayor(Registro* registro){
	};

	bool Nodo::estaIncluido(Registro* registro){
	};

	void Nodo::agregarRegistro(Registro* nuevoRegistro){

	};
    void Nodo::eliminarRegistro(Registro* registroEliminable)
    {

    };
	Lista<Registro*>* Nodo::getListaDeRegistros(){

	};

	// Devuelve una lista de registros que son menores, en clave,
	// al registro pasado por parametro. Los elimina de la lista.
	Lista<Registro*>* Nodo::obtenerRegistrosMenoresA(Registro* registro){

	};

	// Devuelve una lista de registros que son mayores, en clave,
	// al registro pasado por parametro. Los elimina de la lista.
	Lista<Registro*>* Nodo::obtenerRegistrosMayoresA(Registro* registro){

	};

    bool Nodo::encontrarRegistro(Registro* registroModificado,
                           int& posicionDeRegistro)
    {
       this->getListaDeRegistros()->iniciarCursor();
       while(this->getListaDeRegistros()->avanzarCursor())
       {
            if(this->getListaDeRegistros()->obtenerCursor()->getID() == registroModificado->getID())
            {
                return true;
            }
            posicionDeRegistro++;
       }
       return false;
    }
	Nodo::~Nodo(){
	};
