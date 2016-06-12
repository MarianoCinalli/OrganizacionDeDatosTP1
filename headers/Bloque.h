#include <iostream>
#include <string>
#include <sstream>
#include "Registro.h"
#include "Nodo.h"
#include "excepciones/ElNodoExcedeElTamanioMaximo.h"

#ifndef _BLOQUE_H
#define _BLOQUE_H

// Maximo tamanio de datos = tamanio del bloque - cantidad de Bytes para expresar el tamanio del bloque
// 4096 - 2 = 4094
#define MAXIMO_TAMANIO_DE_DATOS 4094

class Bloque {
private:

    std::string hijoIzquierdo;
    std::string hijoDerecho;
    std::string registros;
    unsigned int numeroDeBloque;

public:

    Bloque(Nodo* nodo);

    Bloque(std::string bloqueComoString, unsigned int numeroDeBloque);

    std::string exportarParaEscritura();

    Nodo* exportarComoNodo();

    int getNumeroDeBloque();

private:

    void transformarRegistros(Lista<Registro*>* listaDeRegistros);

    std::string registroAString(Registro* registro);

    std::string transformarEnteroAString(unsigned int entero, unsigned int cantidadDeBytes);

    std::string armarBloque();

    void recuperarInformacion(std::string informacion);

    int recuperarLongitud(std::string cadena);

    unsigned int transformarStringAEntero(std::string cadena);

    Lista<Registro*>* tansformarStringDeRegistrosAListaDeRegistros();

};

#endif // BLOQUE_H
