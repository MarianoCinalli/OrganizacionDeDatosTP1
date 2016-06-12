#include "Archivo.h"

std::fstream Archivo::archivo;

Archivo::Archivo() {

};

// Este constructor carga el path del archivo a escribir.

Archivo::Archivo(std::string direccion) {

    archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);

    // Si el archivo no existe lo crea.
    if ( ! archivo.is_open() ) {
        crearArchivoNuevo(direccion);
    }

};

void Archivo::escribir(Bloque* bloque) {

    int posicion = bloque -> getNumeroDeBloque();

    std::string datos = bloque -> exportarParaEscritura();


    escribirString(datos, posicion);

};

Nodo* Archivo::leer(int numeroDeBloque) {

    if (numeroDeBloque < OFFSET_PRIMER_NODO) throw NumeroDeBloqueInvalido();

    Nodo* nodo;
    Bloque* bloque;

    // Cargo los datos caracter por caracter.
    std::string bloqueComoString = leerString(numeroDeBloque);

    bloque = new Bloque(bloqueComoString, numeroDeBloque);
    nodo = bloque -> exportarComoNodo();

    delete bloque;
    return ( nodo);

};

int Archivo::obtenerNumeroDeBloqueLibre() {

    // Cargar bitmap
    int posicion = 0;
    std::string bitmapComoString;
    char caracter;

    for (unsigned int i = 0; i < TAMANIO_MAXIMO_BLOQUE; i++) {

        archivo.clear();
        archivo.seekp(NUMERO_BLOQUE_BITMAP);
        archivo.read((char *) & caracter, sizeof (char));
        bitmapComoString += caracter;
        posicion++;

    }

    Bitmap* bitmap = new Bitmap(bitmapComoString);
    int posicionUno = bitmap -> obtenerPosicionDelPrimerUno();

    escribirString( bitmap -> obtenerBitmap(), NUMERO_BLOQUE_BITMAP);

    return ( posicionUno + OFFSET_PRIMER_NODO);

};

int Archivo::obtenerPrimerBloqueRegistros(){

    return (OFFSET_PRIMER_NODO);
    
};

void Archivo::escribirRaiz(Bloque* bloque) {

    int posicion = bloque -> getNumeroDeBloque();
    std::string datos = bloque -> exportarParaEscritura();

    escribirString(datos, posicion);

    modificarPosicionRaiz(posicion);

};

// Solo compila con C++11 o C+14.
Nodo* Archivo::leerRaiz() {

    std::string bloque = leerString(NUMERO_BLOQUE_RAIZ);
    int cantidadDeDigitos;
    int posicionDeLaRaiz;

    sscanf(bloque.substr(0, 1).c_str(), "%d", &cantidadDeDigitos);
    sscanf(bloque.substr(1, cantidadDeDigitos).c_str(), "%d", &posicionDeLaRaiz);

    return (leer(posicionDeLaRaiz));

};

Archivo::~Archivo() {

	this -> archivo.close();

};

// Metodos Privados ----------------------------------------------------

void Archivo::escribirString(std::string datos, unsigned int posicionInicialRelativa) {

    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    unsigned int longitudDatos = datos.length();
    char caracter;

    for (unsigned int i = 0; i < longitudDatos; i++) {

        caracter = datos[i];
        archivo.clear();
        archivo.seekp(posicion);
        archivo.write((char*) & caracter, sizeof (char));
        posicion++;

    }

    // Completo con 0 desde el ultimo dato valido.
    for (unsigned int i = posicion; i < TAMANIO_MAXIMO_BLOQUE; i++) {

        caracter = 0;
        archivo.clear();
        archivo.seekp(posicion);
        archivo.write((char*) & caracter, sizeof (char));
        posicion++;

    }

};

std::string Archivo::leerString(unsigned int posicionInicialRelativa) {

    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    char caracter;
    std::string cadenaLeida = "";

    for (unsigned int i = 0; i < TAMANIO_MAXIMO_BLOQUE; i++) {

        archivo.clear();
        archivo.seekp(posicion);
        archivo.read((char *) & caracter, sizeof (char));
        cadenaLeida += caracter;
        posicion++;

    }

    return (cadenaLeida);

};

// Primitiva de creacion:
// Se crea un nuevo archivo con el nombre especificado.
// Se coloca la raiz en el primer nodo libre.
// La misma se encuentra sin registros, ni hijos.
void Archivo::crearArchivoNuevo(std::string direccion) {

    // Trunc crea siempre un archivo nuevo.
    archivo.open(direccion, std::ios::trunc);

    // Lo cierro y lo abro con los parametros necesarios para su manipulacion.
    archivo.close();
    archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);

    // Seteo las condiciones iniciales.
    // Bitmap todos ceros.
    // Guardo la raiz.

};

// Actualiza la posicion de la raiz.
// Escribe en el bloque correspondiente el numero de bloque donde se encuentra la raiz.
void Archivo::modificarPosicionRaiz(unsigned int posicion) {
	
    // Estructura: cantidad de digitos del numero de la raiz + numero de la raiz
    std::string posicionAString = std::to_string(posicion);
    int largo = posicionAString.length();
    // Concateno los campos.
    std::string stringAEscribir = std::to_string(largo) + posicionAString;
    // Persistir.
    escribirString(stringAEscribir, NUMERO_BLOQUE_RAIZ);
    
};
