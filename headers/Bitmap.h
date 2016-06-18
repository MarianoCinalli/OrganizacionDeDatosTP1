#include <iostream>
#include <string>
#include <sstream>

#ifndef _BITMAP_H
#define _BITMAP_H

class Bitmap {
private:

    std::string bitmap;

public:

    Bitmap(std::string bitmap);

    int obtenerPosicionDelPrimerCero();

    std::string obtenerBitmap();

};

#endif // BLOQUE_H
