#include "ArbolBiselado.h"

// Metodos
		
	ArbolBiselado::ArbolBiselado(){
	};

	void ArbolBiselado::insertar(Registro* registro){
		
		insertarRecursivo( registro, this->raiz );
		// biselar(this -> registrosProcesados ,this -> movimientos);
		// liberarMemoria(this -> registrosProcesados);

	};

	bool ArbolBiselado::modificar(Registro* registroAModificar){
		
		return modificarRecursivo(raiz,registroAModificar);
		
	};
	
	void ArbolBiselado::eliminar(int identificador){
	
	};
	/*
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
     */
	
	ArbolBiselado::~ArbolBiselado(){
	};
	
	// Metodos privados ------------------------------------------------
	
	bool ArbolBiselado::modificarRecursivo(Nodo* nodoActual, Registro* registroAModificar){
		
		int posicionRegistro = 0;
		// Te cambie los metodos de los if's por los que van.
		// Creo que necesitas ponerle else a los if's para no evaluar al pedo.
		if (nodoActual -> esElMenor(registroAModificar)){
			modificarRecursivo(nodoActual->getHijoIzquierdo(),registroAModificar);
		}
		
		if(nodoActual-> esElMayor(registroAModificar)){
			modificarRecursivo(nodoActual->getHijoDerecho(),registroAModificar);
		}
		/*
		if(!encontrarRegistroEnNodo(nodoActual,registroAModificar,posicionRegistro)){
			cout << "El registro con el ID ingresado no se encuentra en el árbol." << endl;
			//biselar();
			return false;
		}else{
			
			if(peristirEnDisco(nodoActual,registroAModificar,posicionRegistro)) {
				cout << "Se ha modificado el registro con éxito";
				//biselar();
				return true;
			} else{
				cout << "Ha habido un error en la persistencia de la información";
				//biselar();
				return false;
				}
                
            }
           */
        }
        
        
	// Mariano -----------------------------------------------------
        
	void ArbolBiselado::insertarRecursivo( Registro* registro, Nodo* nodo ){
		
		// this -> registrosProcesados -> apilar(nodo);
		
		if (nodo -> estaIncluido(registro)){
			
			// Excepcion
			// throw elRegistroYaPerteneceAlArbol
			
		} else if (nodo -> esHoja()){
			
				insertarEnHoja(registro, nodo);
				
			} else if ( nodo -> esElMenor(registro) ){
					
					//No se si va a quedar asi.
					//this -> movimientos -> apilar('d');
					avanzarAlHijoDerecho(registro ,nodo);
				
				} else if (nodo -> esElMayor(registro)){
						
						//No se si va a quedar asi.
						//this -> movimientos -> apilar('i');
						avanzarAlHijoIzquierdo(registro ,nodo);
						
					} else {
						
							//insetarDentro(nodo, registro);
						
						}
		
	}
	
	void ArbolBiselado::avanzarAlHijoDerecho(Registro* registro ,Nodo* nodo){
		
		Nodo* hijoDerecho;
		
		try { 
		
			hijoDerecho = nodo -> getHijoDerecho();
			
		} catch ( int e) {
			
			// Creo el nuevo nodo.
			hijoDerecho = new Nodo();
			// Actualizo el numero de bloque.
			nodo -> setNumeroDeBloqueHijoDerecho( hijoDerecho -> getNumeroDeBloque() );
			// Persisto los cambios.
			//persistir(nodo);
			//persistir(hijoIzquierdo);
			
		}
		
		insertarRecursivo(registro ,hijoDerecho);
		
	};
	
	void ArbolBiselado::avanzarAlHijoIzquierdo(Registro* registro ,Nodo* nodo){
		
		Nodo* hijoIzquierdo;
		
		try { 
		
			hijoIzquierdo = nodo -> getHijoIzquierdo();
			
		} catch ( int e) {
			
			// Creo el nuevo nodo.
			hijoIzquierdo = new Nodo();
			// Actualizo el numero de bloque.
			nodo -> setNumeroDeBloqueHijoIzquierdo( hijoIzquierdo -> getNumeroDeBloque() );
			// Persisto los cambios.
			//persistir(nodo);
			//persistir(hijoIzquierdo);
			
		}
		
		insertarRecursivo(registro ,hijoIzquierdo);
		
	};
	
	void ArbolBiselado::insertarEnHoja(Registro* registro ,Nodo* nodo){
		
		try { 
		
			nodo -> agregarRegistro(registro);
			
			
		} catch ( int e) {
			
			// Variables temporales.
			Nodo* hijoIzquierdo;
			Nodo* hijoDerecho;
			
			Lista<Registro*>* registrosHijoIzquierdo;
			Lista<Registro*>* registrosHijoDerecho;
			
			// Parto la lista.
			registrosHijoIzquierdo = nodo -> obtenerRegistrosMenoresA(registro);
			registrosHijoDerecho = nodo -> obtenerRegistrosMayoresA(registro);
			// Creo dos nodos nuevos con los registros.
			hijoIzquierdo = new Nodo(registrosHijoIzquierdo);
			hijoDerecho = new Nodo(registrosHijoDerecho);
			// Actualizo numeros de bloque.
			nodo -> setNumeroDeBloqueHijoIzquierdo ( hijoIzquierdo -> getNumeroDeBloque() );
			nodo -> setNumeroDeBloqueHijoDerecho ( hijoDerecho -> getNumeroDeBloque() );
			// Persisto los cambios.
			//persistir(nodo);
			//persistir(hijoIzquierdo);
			//persistir(hijoDerecho);
			
		}
		
	};
