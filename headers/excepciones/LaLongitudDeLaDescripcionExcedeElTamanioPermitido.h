#ifndef _LALONGITUDDELADESCRIPCIONEXCEDEELTAMANIOPERMITIDO_H
#define _LALONGITUDDELADESCRIPCIONEXCEDEELTAMANIOPERMITIDO_H

class LaLongitudDeLaDescripcionExcedeElTamanioPermitido: public exception{
	
	const char* what() const noexcept {
		
		std::string error =  "La descripcion debe tener entre 1 y 1000 caracteres.";
		return ( error.c_str() );
		
	}

};

#endif // LALONGITUDDELADESCRIPCIONEXCEDEELTAMANIOPERMITIDO_H
