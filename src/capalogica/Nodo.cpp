#include "Nodo.h"
#include "funcionesDePersistencia.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\funcionesDePersistencia.h"
// Metodos

// Constructores
Nodo::Nodo(){

	this -> numeroDeBloqueHijoIzquierdo = 0;
	this -> numeroDeBloqueHijoDerecho = 0;
	this -> registros = new Lista<Registro*>;
	this -> esNodoHoja = true;
	persistir(this);

};

Nodo::Nodo(Lista<Registro*>* registros){

	this -> numeroDeBloqueHijoIzquierdo = 0;
	this -> numeroDeBloqueHijoDerecho = 0;
	this -> registros = registros;
	this -> esNodoHoja = true;
	// La capa fisica le asigna el numero de bloque
	persistir(this);

};

Nodo::Nodo(int hijoDerecho, Lista<Registro*>* listaDeRegistros, int hijoIzquierdo, int numeroDeBloque, bool esHoja){

	this -> numeroDeBloqueHijoIzquierdo = hijoIzquierdo;
	this -> numeroDeBloqueHijoDerecho = hijoDerecho;
	this -> registros = listaDeRegistros;
	this -> esNodoHoja = esHoja;
	this -> numeroDeBloque = numeroDeBloque;

};

// Operaciones con los hijos

void Nodo::setNumeroDeBloqueHijoIzquierdo(int numero){

	this -> esNodoHoja = false;
	this ->numeroDeBloqueHijoIzquierdo = numero;

};

int Nodo::getNumeroDeBloqueHijoIzquierdo()
{
    return this -> numeroDeBloqueHijoIzquierdo;
};

void Nodo::setNumeroDeBloqueHijoDerecho(int numero){

	this -> esNodoHoja = false;
	this -> numeroDeBloqueHijoDerecho = numero;

};

int Nodo::getNumeroDeBloqueHijoDerecho()
{
    return this -> numeroDeBloqueHijoDerecho;
};

Nodo* Nodo::getHijoIzquierdo(){
    //return cargarHijoIzquierdo(this);
};

Nodo* Nodo::getHijoDerecho(){
    //return cargarHijoDerecho(this);
};

// Operaciones de informacion del nodo

int Nodo::getNumeroDeBloque(){

    return numeroDeBloque;

};

void Nodo::setNumeroDeBloque(int nuevoNumeroDeBloque){

	this -> numeroDeBloque = nuevoNumeroDeBloque;

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

   this->getListaDeRegistros()->iniciarCursor();

   while(this->getListaDeRegistros()->avanzarCursor()){
		if(this->getListaDeRegistros()->obtenerCursor()->getCampoIndexante() == registro->getCampoIndexante()){
			return true;
		}
   }

   return false;
};

void Nodo::agregarRegistro(Registro* nuevoRegistro)	{

	registros->agregar(nuevoRegistro);
	persistir(this);

};

void Nodo::eliminarRegistro(Registro* registroEliminable){

	registros -> iniciarCursor();
	int posicion = 0;
	bool encontrado = false;

	while(registros->avanzarCursor() && !encontrado){

		if(registroEliminable->getCampoIndexante() == registros->obtenerCursor()->getCampoIndexante()){

			encontrado = true;

		}
		posicion++;

	}
	registros -> remover(posicion);
	//En el persistir se especifica la grabacion de modificar el bitmap
	//con un nodo vacio? (es decir cambiar su estado de ocupado a libre)
	persistir(this);
	borrarNodoVacio();
};

void Nodo::borrarNodoVacio(){

	if(registros->getTamanio() == 0){

		delete this; // Esto esta feo.

	}

}

Lista<Registro*>* Nodo::getListaDeRegistros(){

	return registros;

};

// Devuelve una lista de registros que son menores, en clave,
// al registro pasado por parametro. Los elimina de la lista. ¿Cuáles elimina?
Lista<Registro*>* Nodo::obtenerRegistrosMenoresA(Registro* registro){

	this -> registros -> obtenerMenoresA(registro);
	
};

// Devuelve una lista de registros que son mayores, en clave,
// al registro pasado por parametro. Los elimina de la lista. ¿Cuáles registros?
Lista<Registro*>* Nodo::obtenerRegistrosMayoresA(Registro* registro){

	Lista<Registro*>* registrosMayores = new Lista<Registro*>;
    int cantidadEliminados = 1;

    registros->iniciarCursor();

    //Busco el primer mayor
    while(registros->avanzarCursor() && *registros->obtenerCursor() < *registro)
    {
    }
    registrosMayores->agregar(registros->obtenerCursor());

    //De ahi en adelante se que son todos mayores y los agrego
	while(registros->avanzarCursor()){

		registrosMayores->agregar(registros->obtenerCursor());
		//voy contando los mayores para saber cuantos eliminar
		cantidadEliminados++;

	}

	//Elimino los registros mayores
    for(int i=1; i<= cantidadEliminados;i++)
    {
        //siempre borro el ultimo
        registros->remover(registros->getTamanio());
    }
	return registrosMayores;
};

bool Nodo::encontrarRegistro(Registro* registroModificado, int& posicionDeRegistro){

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
