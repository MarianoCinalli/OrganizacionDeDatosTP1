#include "funcionesDePersistencia.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\funcionesDePersistencia.h"

// Persiste un nodo en disco.
// Si el nodo tiene mayor tamanio que el permitido se arroja una excepcion.
// Si el nodo tiene un numero de bloque invalido se le asigna uno valido.

void persistir(Nodo* nodo) {
	
    Bloque* bloque;

    try {

        bloque = new Bloque(nodo);

    } catch (ElNodoExcedeElTamanioMaximo e) {

        // Libero recursos. Propago la excepcion.
        delete bloque;
        throw ElNodoExcedeElTamanioMaximo();

    }
    
    Archivo* archivo = new Archivo();

    archivo -> escribir(bloque);

    delete archivo;
    delete bloque;

}

// Carga un nodo del disco a partir de su posicion relativa en el archivo.
// Si el numero de bloque pasado es invalido arroja una excepcion.

Nodo* leer(unsigned int numeroDeBloque) {

    Archivo* archivo = new Archivo();
    Nodo* nodo = archivo -> leer(numeroDeBloque);

    delete archivo;
    return ( nodo);

}

// Guarda la nueva raiz, esta funcion no verifica el tamaño del nodo.
void persistirRaiz(Nodo* nodo) {
	
    Archivo* archivo = new Archivo();
    Bloque* bloque = new Bloque(nodo);

    archivo -> escribirRaiz(bloque);

    delete archivo;
    delete bloque;

}

// Lee la raiz del archivo y devuelve una referencia a ella.
Nodo* leerRaiz() {

    Archivo* archivo = new Archivo();
    Nodo* nodo = archivo -> leerRaiz();

    delete archivo;
    return ( nodo );

}

// Devuelve un numero de bloque libre.
int obtenerNumeroDeBloqueLibre() {

	Archivo* archivo = new Archivo();
    int numeroDeBloqueLibre = archivo -> obtenerNumeroDeBloqueLibre();
    delete archivo;
    
    return ( numeroDeBloqueLibre );

}
