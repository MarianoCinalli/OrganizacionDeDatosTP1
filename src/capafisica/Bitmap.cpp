#include "Bitmap.h"

Bitmap::Bitmap(std::string bitmap) {

    this -> bitmap = bitmap;

};

// Devuelve la posicion del primer cero en el bitmap.
// Marca la posicion con un uno.

int Bitmap::obtenerPosicionDelPrimerCero() {
	
	// Variables
	bool encontrado = false;
	unsigned int i = 0;
	int j = 0;
	unsigned char shifted;
	unsigned char ochoBits;
	unsigned char mascara = 0xFE; // en bits 11111110
	// Fin variables
	
	while (( !encontrado ) && ( i < bitmap.length() )) {
		
		ochoBits = bitmap[i];
		
		while (( !encontrado ) && ( j < 8 )){

			shifted = ochoBits >> j;
			if ( (shifted | mascara) == mascara){
				
				encontrado = true;
				// Pongo un uno en la posicion libre.
				// Invierto los bits de la mascara y la "shifteo" j posiciones.
				ochoBits = ochoBits | (( ~mascara ) << j);
				bitmap[i] = ochoBits;
				
			}
			j++;
			
		}
		i++;
	}
	
	// Si lo encuentro se ejecutan i++ y j++ con lo cual ambas
	// tendran mayor valor del verdadero
	// if ( !encontrado ) throw NO_HAY_BLOQUES_LIBRES_DISPONIBLES
	return ( ( (i - 1) * 8 ) + (j - 1));
	
};

std::string Bitmap::obtenerBitmap() {

    return ( this -> bitmap);

}
