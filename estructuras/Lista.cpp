#include "Lista.h"
#include "NodoSimplementeEnlasado.h"


        	template <class T> Lista<T>::Lista(){};
        	template <class T> unsigned int Lista<T>::getTamanio(){};
            template <class T> bool Lista<T>::estaVacia(){};

        	template <class T> void Lista<T>::agregar(T elemento){};
        	template <class T> void Lista<T>::remover(unsigned int posicion){};

        	template <class T> void Lista<T>::iniciarCursor(){};
        	template <class T> bool Lista<T>::avanzarCursor(){return true;};

        	template <class T> T Lista<T>::obtenerCursor(){};

            template <class T> NodoSimplementeEnlasado<T>* Lista<T>::obtenerNodo(unsigned int posicion){};

