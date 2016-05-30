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

	bool Nodo::esHoja()
	{
	    return esNodoHoja;
	};

	// Operaciones con registros
	bool Nodo::esElMenor(Registro* registro)
	{
	    //asumiendo que los registros se encuentran ordenados
	    getListaDeRegistros()->iniciarCursor();
	    getListaDeRegistros()->avanzarCursor();
	    return registro->getID() < getListaDeRegistros()->obtenerCursor()->getID();
	};

	bool Nodo::esElMayor(Registro* registro)
	{
	    return registro->getID() > getListaDeRegistros()->obtenerUltimo()->getID();
	};

	bool Nodo::estaIncluido(Registro* registro){
	};

	void Nodo::agregarRegistro(Registro* nuevoRegistro)
	{
        registros->agregar(nuevoRegistro);
        //persistir(this); ¿Esto habia que incluir? Es funcion del ArbolBiselado
	};
    void Nodo::eliminarRegistro(Registro* registroEliminable)
    {
        registros->iniciarCursor();
        int posicion = 1;
        while(registros->avanzarCursor())
        {
            if(registroEliminable->getID() == registros->obtenerCursor()->getID())
            {
                break;
            }
            posicion++;
        }
        registros->remover(posicion);
        //persistir(this); ¿Esto habia que incluir? Es funcion del ArbolBiselado
    };
	Lista<Registro*>* Nodo::getListaDeRegistros()
	{
        return registros;
	};

	// Devuelve una lista de registros que son menores, en clave,
	// al registro pasado por parametro. Los elimina de la lista. ¿Cuáles elimina?
	Lista<Registro*>* Nodo::obtenerRegistrosMenoresA(Registro* registro)
	{
        //asumiendo que los registros estan ordenados
        Lista<Registro*>* registrosMenores = new Lista<Registro*>;
        registros->iniciarCursor();
        while(registros->avanzarCursor() &&
              registros->obtenerCursor()->getID() < registro->getID())
        {
            registrosMenores->agregar(registros->obtenerCursor());
        }
        return registrosMenores;
	};

	// Devuelve una lista de registros que son mayores, en clave,
	// al registro pasado por parametro. Los elimina de la lista. ¿Cuáles registros?
	Lista<Registro*>* Nodo::obtenerRegistrosMayoresA(Registro* registro)
	{
	    //asumiendo que los registros estan ordenados
        Lista<Registro*>* registrosMayores = new Lista<Registro*>;
        registros->iniciarCursor();
        while(registros->avanzarCursor())
        {
            if(registros->obtenerCursor()->getID() > registro->getID())
            {
                registrosMayores->agregar(registros->obtenerCursor());
            }
        }
        return registrosMayores;
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
