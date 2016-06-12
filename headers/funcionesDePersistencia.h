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

// NO USAR! -------------------------------------------------------------------

void verificarNumeroDeBloque(Nodo* nodo, Archivo* archivo);

void asignarNumeroDeBloqueLibre(Nodo* nodo, Archivo* archivo);

#endif // FUNCIONESDEPERSISTENCIA_INCLUDED
