#include "Archivo.h"

std::string Archivo::DIRECCION;

void Archivo::setDireccion(std::string direccion){
	
	std::cout << direccion << "\n";
	DIRECCION = direccion;
	std::cout << DIRECCION << "\n";
	
};


Archivo::Archivo() {
	
	std::cout << DIRECCION << "\n";
    this -> archivo.open(DIRECCION, std::fstream::in | std::fstream::out | std::fstream::binary);
    
    // Si el archivo no existe lo crea.
    if ( ! archivo.is_open() ) {
        crearArchivoNuevo();
    }
	archivo.close();

	
};

void Archivo::escribir(Bloque* bloque) {
	
    int posicion = bloque -> getNumeroDeBloque();
	
	if ( bloque -> bloqueSinRegistros() ){
		
		marcarBloqueLibreEnBitmap( bloque -> getNumeroDeBloque() );
		
	} else {
		
			std::string datos = bloque -> exportarParaEscritura();

			escribirString(datos, posicion);
		
		}    

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
	
	// Cargo el bitmap.
    std::string bitmapComoString = leerString(NUMERO_BLOQUE_BITMAP);
    Bitmap* bitmap = new Bitmap(bitmapComoString);
    
    // La siguiente funcion modifica el bitmap.
    int posicionUno = bitmap -> obtenerPosicionDelPrimerCero();
    escribirString( bitmap -> obtenerBitmap(), NUMERO_BLOQUE_BITMAP);
    
	delete ( bitmap );
	
    return ( posicionUno + OFFSET_PRIMER_NODO);

};

int Archivo::obtenerPrimerBloqueRegistros(){

    return (OFFSET_PRIMER_NODO);
    
};

void Archivo::escribirRaiz(Bloque* bloque) {
	cout << "Escribir shaiz" << endl;
    int posicion = bloque -> getNumeroDeBloque();
    cout << "Posicion: " << posicion << endl;
    std::string datos = bloque -> exportarParaEscritura();
	cout << "Datos: " << datos << endl;
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
	
};

// Metodos Privados ----------------------------------------------------

void Archivo::escribirString(std::string datos, unsigned int posicionInicialRelativa) {
	
	this -> archivo.open(DIRECCION, std::fstream::in | std::fstream::out | std::fstream::binary);
	
    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    unsigned int longitudDatos = datos.length();
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
	
	this -> archivo.open(DIRECCION, std::fstream::in | std::fstream::out | std::fstream::binary);
	
    unsigned int posicion = posicionInicialRelativa * TAMANIO_MAXIMO_BLOQUE;
    char caracter;
    std::string cadenaLeida = "";

    for (unsigned int i = 0; i < TAMANIO_MAXIMO_BLOQUE; i++) {

        archivo.seekp(posicion);
        archivo.read((char *) & caracter, sizeof (char));
        cadenaLeida += caracter;
        posicion++;

    }
    
	this -> archivo.close();
	
    return (cadenaLeida);

};

// Primitiva de creacion:
// Se crea un nuevo archivo con el nombre especificado.
// Se coloca la raiz en el primer nodo libre.
// La misma se encuentra sin registros, ni hijos.
void Archivo::crearArchivoNuevo() {

    // Trunc crea siempre un archivo nuevo.
    archivo.open(DIRECCION, std::fstream::out | std::ios::trunc);

    // Lo cierro y lo abro con los parametros necesarios para su manipulacion.
    archivo.close();
    // Seteo las condiciones iniciales.
    
    // Esto pone todos los bits anteriores al guardado en cero.
    //escribir(bloque);
    modificarPosicionRaiz(2);
    // Esta funcion va a poner un uno en la posicion 0 del bitmap.
    // Que corresponde a la posicion de la raiz.
    obtenerNumeroDeBloqueLibre();
    
};

// Actualiza la posicion de la raiz.
// Escribe en el bloque correspondiente el numero de bloque donde se encuentra la raiz.
void Archivo::modificarPosicionRaiz(unsigned int posicion) {
	
	this -> archivo.open(DIRECCION, std::fstream::in | std::fstream::out | std::fstream::binary);
    // Estructura: cantidad de digitos del numero de la raiz + numero de la raiz
    std::string posicionAString = std::to_string(posicion);
    int largo = posicionAString.length();
    // Concateno los campos.
    std::string stringAEscribir = std::to_string(largo) + posicionAString;
    // Persistir.
    escribirString(stringAEscribir, NUMERO_BLOQUE_RAIZ);
    
};

// Modifica el bitmap para indicar que el bloque esta libre
void Archivo::marcarBloqueLibreEnBitmap( unsigned int posicion ){
	
	std::string bitmapComoString = leerString(NUMERO_BLOQUE_BITMAP);
    Bitmap* bitmap = new Bitmap(bitmapComoString);
    
	bitmap -> marcarConCero( posicion - OFFSET_PRIMER_NODO );
	escribirString( bitmap -> obtenerBitmap(), NUMERO_BLOQUE_BITMAP);
	
	delete ( bitmap );
	
};
