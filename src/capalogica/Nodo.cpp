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
	
    return ( leer( this -> numeroDeBloqueHijoIzquierdo ) );
    
};

Nodo* Nodo::getHijoDerecho(){
	
    return ( leer( this -> numeroDeBloqueHijoDerecho) );
    
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

// Esto no funciona tenes que borrrar el objeto afuera de la clase.
// Podes usar el metodo que puse yo para saber si el nodo esta vacio.
// nodo -> estaVacio();
// Esto lo haces en el arbol.
void Nodo::borrarNodoVacio(){

	if(registros->getTamanio() == 0){

		delete this; // Esto esta feo.

	}

}

Lista<Registro*>* Nodo::getListaDeRegistros(){

	return registros;

};

// Devuelve una lista de registros que son menores, en clave,
// al registro pasado por parametro. Los remueve del nodo.
Lista<Registro*>* Nodo::obtenerRegistrosMenoresA(Registro* registro){

	return ( this -> registros -> obtenerMenoresA(registro) );

};

// Devuelve una lista de registros que son mayores, en clave,
// al registro pasado por parametro. Los remueve del nodo.
Lista<Registro*>* Nodo::obtenerRegistrosMayoresA(Registro* registro){
	
    return ( this -> registros -> obtenerMayoresA(registro) );
    
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

bool Nodo::estaVacio(){
	
		return ( registros -> estaVacia() );
};

Nodo::~Nodo(){
	
	delete (this -> registros);
};
