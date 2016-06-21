#include <iostream>
#include <string>
#include "Registro.h"
#include "Nodo.h"
#include "Bloque.h"
#include "Archivo.h"
#include "excepciones/ElNodoExcedeElTamanioMaximo.h"

#ifndef FUNCIONESDEPERSISTENCIA_INCLUDED
#define FUNCIONESDEPERSISTENCIA_INCLUDED

void persistir(Nodo* nodo);

Nodo* leer(unsigned int numeroDeBloque);

void persistirRaiz(Nodo* nodo);

Nodo* leerRaiz();

int obtenerNumeroDeBloqueLibre();

#endif // FUNCIONESDEPERSISTENCIA_INCLUDED
