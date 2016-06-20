#include <iostream>
#include <string>
#include <getopt.h>
#include <stdlib.h>
#include <sstream>

#include "Registro.h"
#include "Nodo.h"
#include "funcionesDePersistencia.h"
#include "ArbolBiselado.h"
#include "excepciones/LaLongitudDelCodigoExcedeElTamanioPermitido.h"
#include "excepciones/LaLongitudDeLaDescripcionExcedeElTamanioPermitido.h"

//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\ArbolBiselado.h"

void PrintHelp(){
	
    std::cout <<
            "--a:             Alta del registro formado porlos parametros indicados en -i -c -d \n"
            "--b:             Baja del registro formado porlos parametros indicados en -i -c -d \n"
            "--m:             Modificacion el registro formado porlos parametros indicados en -i -c -d \n"
            "--i:             ID del registro \n"
            "--c:             Codigo del registro \n"
            "--d:             Descripcion del registro \n"
            "--r: 			  Direccion del arbol \n"
            "--help:          Show help \n";
            
}

void verificarEntrada( std::string codigo, std::string descripcion){

	if ( codigo.length() > 3 ) throw LaLongitudDelCodigoExcedeElTamanioPermitido();
	if ( descripcion.length() > 1000 ) throw LaLongitudDeLaDescripcionExcedeElTamanioPermitido();
	
};

void altaDeRegistro(unsigned int id, std::string codigo, std::string descripcion,std::string ruta){
	
	verificarEntrada( codigo, descripcion);
	
	Archivo* archivo = new Archivo(ruta);
	Registro* registro = new Registro( id, codigo, descripcion );
	ArbolBiselado* arbolBiselado = new ArbolBiselado( archivo -> leerRaiz() );
	
	arbolBiselado -> insertar(registro);
	
	delete arbolBiselado;
	delete archivo;
	
};

void bajaDeRegistro(unsigned int id, std::string codigo, std::string descripcion,std::string ruta){
	
	verificarEntrada( codigo, descripcion);
	
	Archivo* archivo = new Archivo(ruta);
	Registro* registro = new Registro( id, codigo, descripcion );
	ArbolBiselado* arbolBiselado = new ArbolBiselado( archivo -> leerRaiz() );
	
	arbolBiselado -> eliminar(registro);
	
	delete arbolBiselado;
	delete archivo;
	
};

void modificacionDeRegistro(unsigned int id, std::string codigo, std::string descripcion,std::string ruta){
	
	verificarEntrada( codigo, descripcion);
	
	Archivo* archivo = new Archivo(ruta);
	Registro* registro = new Registro( id, codigo, descripcion );
	ArbolBiselado* arbolBiselado = new ArbolBiselado( archivo -> leerRaiz() );
	
	arbolBiselado -> modificar(registro);
	
	delete arbolBiselado;
	delete archivo;
	
};

int main(int argc, char* argv[]){
	
	// Variables -------------------------------------------------------

	std::string ruta, codigo, descripcion;
	bool alta, baja, modificacion;
	alta = modificacion = baja = false;
	unsigned int id;
	
	const char* const short_opts = "n:bs:w:h";
    
    const option long_opts[] = {
		
            {"alta", 0, NULL, 'a'},
            {"baja", 0, NULL, 'b'},
            {"modificacion", 0, NULL, 'm'},
            {"id", 1, NULL, 'i'},
            {"codigo", 1, NULL, 'c'},
            {"descripcion", 1, NULL, 'd'},
            {"ruta", 1, NULL, 'r'},
            {NULL, 0, NULL, 0}
            
    };
    
    // Fin variables ---------------------------------------------------

    while (true){
		
        int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

        if (-1 == opt) break;

        switch (opt){
			
	        case 'a':
	            alta = true;
	            break;
	
	        case 'b':
	            baja = true;
	            break;
	
	        case 'm':
	            modificacion = true;
	            break;
	            
	        case 'i':
	            id  = std::stoi(optarg);
	            break;
	            
	        case 'c':
	            codigo = std::string(optarg);
	            break;
	            
	        case 'd':
	            descripcion = std::string(optarg);
	            break;
	
	        case 'r':
	            ruta = std::string(optarg);

		}
	
	}
	
	try {
		
		if (alta) {
			
			altaDeRegistro(id, codigo, descripcion, ruta);
			
		} else if (baja) {
			
			bajaDeRegistro(id, codigo, descripcion, ruta);
			
		} else if (modificacion) {
			
			modificacionDeRegistro(id, codigo, descripcion, ruta);
			
		} else {
			
			PrintHelp();
			
		}
	
	} catch ( const std::exception& e ){
	
		std::cout << e.what() << "\n";
	
	}
	return EXIT_SUCCESS;
	
}
