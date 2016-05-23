#include "Nodo.h"
	// Metodos
	Nodo::Nodo(){
		
		this -> numeroDeBloqueHijoIzquierdo = 0;
		this -> numeroDeBloqueHijoDerecho = 0;
		this -> hijoIzquierdo = NULL;
		this -> hijoDerecho = NULL;
		this -> registros = new Lista<Registro>;
		this -> esNodoHoja = true;
		
	};

	void Nodo::setNumeroDeBloqueHijoIzquierdo(int numero){
	};
	
	int Nodo::getNumeroDeBloqueHijoIzquierdo(){
	};

	void Nodo::setNumeroDeBloqueHijoDerecho(int numero){
	};
	
	int Nodo::getNumeroDeBloqueHijoDerecho(){
	};

	void Nodo::setHijoIzquierdo(Nodo* hijoIzquierdo){
	};
	
	Nodo* Nodo::getHijoIzquierdo(){
	};

	void Nodo::setHijoDerecho(Nodo* hijoDerecho){
	};
	
	Nodo* Nodo::getHijoDerecho(){
	};
	
	// Esto vuela
	int Nodo::getMenorClave(){ 
		return 1; 
	};
	
	int Nodo::getMayorClave(){ 
		return 1; 
	};
	
	// Y se reemplaza por
	bool Nodo::esElMenor(Registro* registro){
	};
	
	bool Nodo::esElMayor(Registro* registro){
	};
	
	bool Nodo::estaIncluido(Registro* registro){
	};
	
	bool Nodo::esHoja(){
	};

	Lista<Registro>* Nodo::getListaDeRegistros(){
		
	};

	Nodo::~Nodo(){
	};
