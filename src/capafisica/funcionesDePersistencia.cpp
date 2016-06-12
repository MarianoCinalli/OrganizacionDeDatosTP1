#include "funcionesDePersistencia.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\funcionesDePersistencia.h"

// Persiste un nodo en disco.
// Si el nodo tiene mayor tamanio que el permitido se arroja una excepcion.
// Si el nodo tiene un numero de bloque invalido se le asigna uno valido.

void persistir(Nodo* nodo) {

    Archivo* archivo = new Archivo();
    Bloque* bloque;

    verificarNumeroDeBloque(nodo, archivo);

    try {

        bloque = new Bloque(nodo);

    } catch (ElNodoExcedeElTamanioMaximo e) {

        // Libero recursos. Propago la excepcion.
        delete archivo;
        delete bloque;
        throw ElNodoExcedeElTamanioMaximo();

    }

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

// Las dos funciones siguientes son para llamar en el main. NO USAR EN OTRO LADO.

// Guarda la nueva raiz, esta funcion no verifica el tamaño del nodo.

void persistirRaiz(Nodo* nodo) {

    Archivo* archivo = new Archivo();
    Bloque* bloque = new Bloque(nodo);

    archivo -> escribirRaiz(bloque);

    delete archivo;
    delete bloque;

}

Nodo* leerRaiz() {

    Archivo* archivo = new Archivo();
    Nodo* nodo = archivo -> leerRaiz();

    delete archivo;
    return ( nodo);

}

// Futuro refactor -----------------------------------------------------

// Verifica que el numero de bloque sea valido.
// Si no lo es le asigna el numero del primer bloque libre.
// Esto ultimo solo pasa cuando se cree un nodo nuevo.

void verificarNumeroDeBloque(Nodo* nodo, Archivo* archivo) {

    int primerBloqueRegistros = archivo -> obtenerPrimerBloqueRegistros();
    int numeroDeBloque = nodo -> getNumeroDeBloque();

    if (numeroDeBloque < primerBloqueRegistros) asignarNumeroDeBloqueLibre(nodo, archivo);

}

// Asigna a un nodo un numero de bloque libre.

void asignarNumeroDeBloqueLibre(Nodo* nodo, Archivo* archivo) {

    int numeroDeBloqueLibre = archivo -> obtenerNumeroDeBloqueLibre();
    nodo -> setNumeroDeBloque(numeroDeBloqueLibre);

}
