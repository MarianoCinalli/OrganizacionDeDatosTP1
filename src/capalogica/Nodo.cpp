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
	// Como es un registro nuevo le pido un numero de bloque libre
	// a la capa fisica.
	this -> numeroDeBloque = obtenerNumeroDeBloqueLibre();

};

Nodo::Nodo( Lista<Registro*>* registros ){

	this -> numeroDeBloqueHijoIzquierdo = 0;
	this -> numeroDeBloqueHijoDerecho = 0;
	this -> registros = registros;
	this -> esNodoHoja = true;
	// Como es un registro nuevo le pido un numero de bloque libre
	// a la capa fisica.
	this -> numeroDeBloque = obtenerNumeroDeBloqueLibre();

};

Nodo::Nodo(unsigned int hijoDerecho, Lista<Registro*>* listaDeRegistros, unsigned int hijoIzquierdo, unsigned int numeroDeBloque, bool esHoja){

	this -> numeroDeBloqueHijoIzquierdo = hijoIzquierdo;
	this -> numeroDeBloqueHijoDerecho = hijoDerecho;
	this -> registros = listaDeRegistros;
	this -> esNodoHoja = esHoja;
	this -> numeroDeBloque = numeroDeBloque;

};

// Operaciones con los hijos

void Nodo::setNumeroDeBloqueHijoIzquierdo(unsigned int  numero){

	this -> esNodoHoja = false;
	this -> numeroDeBloqueHijoIzquierdo = numero;

};

unsigned int  Nodo::getNumeroDeBloqueHijoIzquierdo(){
	
    return this -> numeroDeBloqueHijoIzquierdo;
    
};

void Nodo::setNumeroDeBloqueHijoDerecho(unsigned int numero){

	this -> esNodoHoja = false;
	this -> numeroDeBloqueHijoDerecho = numero;

};

unsigned int Nodo::getNumeroDeBloqueHijoDerecho(){
	
    return this -> numeroDeBloqueHijoDerecho;
    
};

Nodo* Nodo::getHijoIzquierdo(){

    return ( leer( this -> numeroDeBloqueHijoIzquierdo ) );

};

Nodo* Nodo::getHijoDerecho(){

    return ( leer( this -> numeroDeBloqueHijoDerecho) );

};

// Operaciones de informacion del nodo

unsigned int Nodo::getNumeroDeBloque(){

    return ( this -> numeroDeBloque );

};

void Nodo::setNumeroDeBloque(unsigned int nuevoNumeroDeBloque){

	this -> numeroDeBloque = nuevoNumeroDeBloque;

};

bool Nodo::esHoja(){

    return ( this -> esNodoHoja );

};

// Operaciones con registros
bool Nodo::esElMenor(Registro* registro){

    this -> registros-> iniciarCursor();
    this -> registros-> avanzarCursor();
    Registro* primerRegistro = registros -> obtenerCursor();

    return ( *registro < *primerRegistro);

};

bool Nodo::esElMayor(Registro* registro){

	this-> registros -> iniciarCursor();
	Registro* ultimoRegistro = registros -> obtenerUltimo();

    return ( *registro > *ultimoRegistro );

};

bool Nodo::estaIncluido(Registro* registro){

   this-> registros ->iniciarCursor();

   while ( this-> registros -> avanzarCursor() ){
	   
		if( *(this-> registros -> obtenerCursor()) == *registro ){
			
			return true;
			
		}
		
   }

   return false;
   
};

void Nodo::agregarRegistro(Registro* nuevoRegistro)	{
	registros -> agregar(nuevoRegistro);
	persistir(this);

};

void Nodo::eliminarRegistro(Registro* registroEliminable){

	remover( registroEliminable );
    persistir(this);

};

void Nodo::modificarRegistro( Registro* registro ){

	remover( registro );
	agregarRegistro( registro );

}

void Nodo::remover( Registro* registroEliminable ){
	
	this -> registros -> iniciarCursor();
	int posicion = 0;
	bool encontrado = false;

	while( registros -> avanzarCursor() && !encontrado ){

		if( *registroEliminable == *(this -> registros -> obtenerCursor()) ){

			encontrado = true;

		}
		posicion++;

	}
	
	this -> registros -> remover(posicion);
	
}

// Esto no funciona tenes que borrrar el objeto afuera de la clase.
// Podes usar el metodo que puse yo para saber si el nodo esta vacio.
// nodo -> estaVacio();
// Esto lo haces en el arbol.

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

   while(this-> registros ->avanzarCursor()){

		if( *(this-> registros -> obtenerCursor()) == *registroModificado ){
			return true;
		}

		posicionDeRegistro++;
   }

   return false;
}

bool Nodo::estaVacio(){

	return ( this -> registros -> estaVacia() );
	
};

Nodo::~Nodo(){
	
	persistir (this);
	delete (this -> registros);
	
};
