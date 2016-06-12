#include "Bitmap.h"

Bitmap::Bitmap(std::string bitmap) {

    this -> bitmap = bitmap;

};

// Devuelve la posicion del primer cero en el bitmap.
// Marca la posicion con un uno.

int Bitmap::obtenerPosicionDelPrimerUno() {

    std::size_t posicionDelCero = bitmap.find('0');

    // Se podria tirar una excepcion si te quedas sin
    // bloques libres si sobra tiempo estaria bueno hacerlo.
    // if (found == std::string::npos) throw TeQuedasteSinBloquesLibresPapa;

    this -> bitmap[posicionDelCero] = 1;

    // La funcion del return puede tirar un warning porque podria pasar un overflow.
    return (static_cast<int> (posicionDelCero));

};

std::string Bitmap::obtenerBitmap() {

    return ( this -> bitmap);

}