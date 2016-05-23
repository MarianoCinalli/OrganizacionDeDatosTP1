#include "ArbolBiselado.h"

// Metodos
		
	ArbolBiselado::ArbolBiselado(){
	};

	void ArbolBiselado::insertar(Registro* registro){
		
		insertarRecursivo( registro, this->raiz );
		
	};

	bool ArbolBiselado::modificar(Registro* registroAModificar){
		
		return modificarRecursivo(raiz,registroAModificar);
		
	}
	
	void ArbolBiselado::eliminar(int identificador){
	
	};

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
	
	// Metodos privados ------------------------------------------------
	
	bool ArbolBiselado::modificarRecursivo(Nodo* nodoActual, Registro* registroAModificar){
		
		int posicionRegistro = 0;
		
		if (nodoActual->getMenorClave() > registroAModificar->getID()){
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}
		
		if(nodoActual->getMayorClave() < registroAModificar->getID()){
			modificarRecursivo(nodoActual->getHijoDerecho(),registroAModificar);
		}
		
		if(!encontrarRegistroEnNodo(nodoActual,registroAModificar,posicionRegistro)){
			cout << "El registro con el ID ingresado no se encuentra en el árbol." << endl;
			//biselar();
			return false;
		}else{
			/*
			if(peristirEnDisco(nodoActual,registroAModificar,posicionRegistro)) {
				cout << "Se ha modificado el registro con éxito";
				//biselar();
				return true;
			} else{
				cout << "Ha habido un error en la persistencia de la información";
				//biselar();
				return false;
				}
                */
            }
        }
        
	// Mariano -----------------------------------------------------
        
	void ArbolBiselado::insertarRecursivo( Registro* registro, Nodo* nodo ){
		
		if (nodo -> estaIncluido(registro)){
			
			// Excepcion
			
		} else if (nodo -> esHoja()){
			
				//insertarEnHoja(registro, nodo);
				
			} else if ( nodo -> esElMenor(registro) ){
			
					Nodo* hijoDerecho = nodo -> getHijoDerecho();
					insertarRecursivo(registro ,hijoDerecho);
				
				} else if (nodo -> esElMayor(registro)){
			
						Nodo* hijoIzquierdo = nodo -> getHijoIzquierdo();
						insertarRecursivo(registro ,hijoIzquierdo);
						
					} else {
						
							//insetarDentro(nodo, registro);
						
						}
		
	}
