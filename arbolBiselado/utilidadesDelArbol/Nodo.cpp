#include "Nodo.h"
	// Metodos
		Nodo::Nodo(){};

		void Nodo::setNumeroDeBloqueHijoIzquierdo(int numero){};
		int Nodo::getNumeroDeBloqueHijoIzquierdo(){};

		void Nodo::setNumeroDeBloqueHijoDerecho(int numero){};
		int Nodo::getNumeroDeBloqueHijoDerecho(){};

		void Nodo::setHijoIzquierdo(Nodo* hijoIzquierdo){};
		Nodo* Nodo::getHijoIzquierdo(){};

		void Nodo::setHijoDerecho(Nodo* hijoDerecho){};
		Nodo* Nodo::getHijoDerecho(){};

		int Nodo::getMenorClave(){};
		int Nodo::getMayorClave(){};

		Lista<Registro>* Nodo::getListaDeRegistros(){};

		Nodo::~Nodo(){};
