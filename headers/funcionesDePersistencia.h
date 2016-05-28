#include <iostream>
#include <string>
#include "Registro.h"
#include "Nodo.h"

#ifndef FUNCIONESDEPERSISTENCIA_INCLUDED
#define FUNCIONESDEPERSISTENCIA_INCLUDED

// CONSTANTES

#define TAMANIO_MAXIMO_BLOQUE = 2048;
// Primer bloque = bit map. 1 ocupado. 0 libre.
#define NUMERO_BLOQUE_BITMAP = 1;
// Offset para el primer bloque donde se encuentra un nodo.
#define OFFSET_PRIMER_NODO = 1;
// Segundo bloque = numero de bloque de la raiz.
#define NUMERO_BLOQUE_RAIZ = 2;

void persistir( Nodo* nodo );

#endif // FUNCIONESDEPERSISTENCIA_INCLUDED
