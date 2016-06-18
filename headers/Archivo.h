#include "Nodo.h"
#include "Bloque.h"
#include "Bitmap.h"
#include "excepciones/NumeroDeBloqueInvalido.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

#ifndef ARCHIVO_H
#define ARCHIVO_H

// CONSTANTES

#define TAMANIO_MAXIMO_BLOQUE 4096
// Primer bloque = bit map.
#define NUMERO_BLOQUE_BITMAP 0
// Segundo bloque = numero de bloque de la raiz.
#define NUMERO_BLOQUE_RAIZ 1
// Offset para el primer bloque donde se encuentra un nodo.
#define OFFSET_PRIMER_NODO 2

class Archivo {
	
private:
	
	static std::string direccion;
    std::fstream archivo;

public:

    Archivo();
    Archivo(std::string direccion);

    void escribir(Bloque* bloque);
    void escribirRaiz(Bloque* bloque);
    Nodo* leer(int numeroDeBloque);
    Nodo* leerRaiz();
    
    int obtenerNumeroDeBloqueLibre();
    int obtenerPrimerBloqueRegistros();
    
    ~Archivo();

private:

    void escribirString(std::string datos, unsigned int posicionInicial);
    std::string leerString(unsigned int posicionInicial);
    void crearArchivoNuevo(std::string direccion);
    void modificarPosicionRaiz(unsigned int posicion);

};

#endif // ARCHIVO_H
