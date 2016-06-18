#include "Archivo.h"

std::string Archivo::direccion;

Archivo::Archivo() {

};

// Este constructor carga el path del archivo a escribir.

Archivo::Archivo(std::string direccion) {
	
	this -> direccion = direccion;
    this -> archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);
    
    // Si el archivo no existe lo crea.
    if ( ! archivo.is_open() ) {
        crearArchivoNuevo(direccion);
    }
	archivo.close();

	
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
    return (nodo);

};

int Archivo::obtenerNumeroDeBloqueLibre() {

    // Cargar bitmap
    int posicion = NUMERO_BLOQUE_BITMAP;
    std::string bitmapComoString;
    char caracter;

    for (unsigned int i = 0; i < TAMANIO_MAXIMO_BLOQUE; i++) {
		
        archivo.clear();
        archivo.seekp(posicion);
        archivo.read((char *) & caracter, sizeof (char));
        bitmapComoString += caracter;
        posicion++;

    }
	
    Bitmap* bitmap = new Bitmap(bitmapComoString);
    int posicionUno = bitmap -> obtenerPosicionDelPrimerCero();
    escribirString( bitmap -> obtenerBitmap(), NUMERO_BLOQUE_BITMAP);
	delete ( bitmap );
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
	std::cout << "CANTIDAD DE DIGITOS: " << cantidadDeDigitos << "\n";
    sscanf(bloque.substr(1, cantidadDeDigitos).c_str(), "%d", &posicionDeLaRaiz);
	std::cout << "POSICION DE LA RAIZ: " << posicionDeLaRaiz << "\n";
    return (leer(posicionDeLaRaiz));

};

Archivo::~Archivo() {
	
};

// Metodos Privados ----------------------------------------------------

void Archivo::escribirString(std::string datos, unsigned int posicionInicialRelativa) {
	
	this -> archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);
	
	std::cout << "DATOS: " << datos << "\n";
	std::cout << "POSICION RELATIVA: " << posicionInicialRelativa << "\n";
    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    std::cout << "POSICION ABSOLUTA: " << posicion << "\n";
    unsigned int longitudDatos = datos.length();
    std::cout << "LONGITUD: " << longitudDatos << "\n";
    std::cout << "\n";
    char caracter;
	
    for (unsigned int i = 0; i < longitudDatos; i++) {
		
		archivo.clear();
        caracter = datos[i];
        archivo.seekp(posicion);
        archivo.write((char*) & caracter, sizeof (char));
        posicion++;

    }

    // Completo con 0 desde el ultimo dato valido.
    
    for (unsigned int i = posicion; i <  (posicionInicialRelativa + 1)*TAMANIO_MAXIMO_BLOQUE; i++) {

        caracter = 0x00;
        archivo.seekp(posicion);
        archivo.write((char*) & caracter, sizeof (char));
        posicion++;

    }
	
	this -> archivo.close();
};

std::string Archivo::leerString(unsigned int posicionInicialRelativa) {
	
	this -> archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);
	
    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    char caracter;
    std::string cadenaLeida = "";

    for (unsigned int i = 0; i < TAMANIO_MAXIMO_BLOQUE; i++) {

        archivo.seekp(posicion);
        archivo.read((char *) & caracter, sizeof (char));
        cadenaLeida += caracter;
        posicion++;

    }
    
    //std::cout << cadenaLeida << "\n";
    
	this -> archivo.close();
	
    return (cadenaLeida);

};

// Primitiva de creacion:
// Se crea un nuevo archivo con el nombre especificado.
// Se coloca la raiz en el primer nodo libre.
// La misma se encuentra sin registros, ni hijos.
void Archivo::crearArchivoNuevo(std::string direccion) {
	// NO TOQUES ESTO QUE LE ME FALTA HACER ALGO PARA QUE FUNCIONE BIEN.
    // Trunc crea siempre un archivo nuevo.
    archivo.open(direccion, std::fstream::out | std::ios::trunc);

    // Lo cierro y lo abro con los parametros necesarios para su manipulacion.
    archivo.close();
    // Seteo las condiciones iniciales.
    // Raiz sin hijos, sin registros, en el primer bloque libre el 3.
    Lista<Registro*>* registros = new Lista<Registro*>;
    Nodo* raiz = new Nodo(320, registros, 300, 2, true);
    Registro* registro= new Registro(300,"a92","Buena Descripcion");
    raiz -> agregarRegistro(registro);
    
    //Bloque* bloque = new Bloque ( raiz );
    // Esto pone todos los bits anteriores al guardado en cero.
    //escribir(bloque);
    modificarPosicionRaiz(2);
    // Esta funcion va a poner un uno en la posicion 0 del bitmap.
    // Que corresponde a la posicion de la raiz.
    int entero = obtenerNumeroDeBloqueLibre();
    //std::cout << entero << "\n";
    // Guardo la raiz.
    // La lista se libera en el destructor de la raiz.
    delete (raiz);
    //delete (bloque);
    
};

// Actualiza la posicion de la raiz.
// Escribe en el bloque correspondiente el numero de bloque donde se encuentra la raiz.
void Archivo::modificarPosicionRaiz(unsigned int posicion) {
	
	this -> archivo.open(direccion, std::fstream::in | std::fstream::out | std::fstream::binary);
    // Estructura: cantidad de digitos del numero de la raiz + numero de la raiz
    std::string posicionAString = std::to_string(posicion);
    int largo = posicionAString.length();
    // Concateno los campos.
    std::string stringAEscribir = std::to_string(largo) + posicionAString;
    // Persistir.
    escribirString(stringAEscribir, NUMERO_BLOQUE_RAIZ);
    
};
