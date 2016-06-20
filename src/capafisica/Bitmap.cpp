#include "Bitmap.h"

Bitmap::Bitmap(std::string bitmap) {

    this -> bitmap = bitmap;

};

// Devuelve la posicion del primer cero en el bitmap.
// Marca la posicion con un uno.

int Bitmap::obtenerPosicionDelPrimerCero() {
	
	// Variables -------------------------------------------------------
	bool encontrado = false;
	unsigned int i = 0;
	int j = 0;
	unsigned char shifted;
	unsigned char ochoBits;
	unsigned char mascara = 0xFE; // en bits 11111110
	// Fin variables ---------------------------------------------------
	
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

// Coloca un 0 en la posicion indicada del bitmap.
void Bitmap::marcarConCero(unsigned int posicion){

	// Variables -------------------------------------------------------
	unsigned int cociente = posicion / 8;
	unsigned int resto = posicion % 8;
	unsigned int i;
	unsigned char ochoBits = bitmap[0];
	char mascara = 0xBF; // En bits 10111111	
	// Fin variables ---------------------------------------------------
	
	// Obtengo los 8 bits en los que esta el bit a poner en cero.
	for (i = 0; i < cociente; i++ ){
	
		ochoBits = bitmap[i];
	
	}
	
	// Armo la mascara con los bits en la posicion necesaria.
	if ( resto == 0 ){ 
		
		mascara = 0x7F; // En bits 01111111
		
	} else {
		// Como la mascara es un caracter con signo, arrastra el ultimo uno.
		resto--; 
		mascara = mascara >> resto;
				
		}
	
	// El and deja pasar todos los bits y en la posicion pone un 0.
	ochoBits = ochoBits & mascara;
	bitmap[i] = ochoBits;

}
