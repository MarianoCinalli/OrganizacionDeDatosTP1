#ifndef _LALONGITUDDELCODIGOEXEDEELTAMANIOPERMITIDO_H
#define _LALONGITUDDELCODIGOEXEDEELTAMANIOPERMITIDO_H

class LaLongitudDelCodigoExcedeElTamanioPermitido: public exception{

	const char* what() const noexcept {
		
		std::string error = "El codigo debe tener entre 1 y 3 caracteres.";

		return ( error.c_str() );
		
	}

};

#endif // LA_LONGITUD_DEL_CODIGO_EXEDE_EL_TAMANIO_PERMITIDO_H
