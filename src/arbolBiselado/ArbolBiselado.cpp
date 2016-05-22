#include "ArbolBiselado.h"

// Metodos
		
	ArbolBiselado::ArbolBiselado(){
	};

	void ArbolBiselado::insertar(Registro* registro){
	};

	bool ArbolBiselado::modificar(Registro* registroAModificar){
		return modificarRecursivo(raiz,registroAModificar);
	}
	void ArbolBiselado::eliminar(int identificador){};

	bool ArbolBiselado::modificarRecursivo(Nodo* nodoActual, Registro* registroAModificar){
		
		int posicionRegistro = 0;
		
		if (nodoActual->getMenorClave() > registroAModificar->getID()){
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}
		
		if(nodoActual->getMayorClave() < registroAModificar->getID()){
			modificarRecursivo(nodoActual->getHijoDerecho(),registroAModificar);
		}
		
		if(!encontrarRegistroEnNodo(nodoActual,registroAModificar,posicionRegistro)){
			cout << "El registro con el ID ingresado no se encuentra en el �rbol." << endl;
			//biselar();
			return false;
		}else{
			/*
			if(peristirEnDisco(nodoActual,registroAModificar,posicionRegistro)) {
				cout << "Se ha modificado el registro con �xito";
				//biselar();
				return true;
			} else{
				cout << "Ha habido un error en la persistencia de la informaci�n";
				//biselar();
				return false;
				}
                */
            }
        }

	bool ArbolBiselado::encontrarRegistroEnNodo(Nodo* nodoActual, Registro* registroModificado, int& posicionDeRegistro){
		
		nodoActual->getListaDeRegistros()->iniciarCursor();
		
		while(nodoActual->getListaDeRegistros()->avanzarCursor()){
			
			if(nodoActual->getListaDeRegistros()->obtenerCursor().getID() == registroModificado->getID()){
				return true;
			}
			posicionDeRegistro++;
       }
       
       return false;
     }
	
	ArbolBiselado::~ArbolBiselado(){
	};

