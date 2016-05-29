#include <string>
#include "Registro.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Registro.h"
using namespace std;
	// Metodos
		Registro::Registro(){};
		Registro::Registro(string campoIndexante){};

		unsigned int Registro::getID(){};
		void Registro::setID(unsigned int nuevoID){};

		int Registro::getCodigo(){};
		void Registro::setCodigo(int nuevoCodigo){};

		string Registro::getDescripcion(){};
		void Registro::setDescripcion(string nuevaDescripcion){};

		// Esto es poque al iniciar el arbol se elije el campo para usar como identificador.
		// Si al principo te dicen que se ordena por ID aca devolves la ID, osea no usas el getID para recorrer el arbol.
		// Lo mismo si se elije codigo.
		// Aca hay que setear la variable estatica. El lunes lo hablamos de ultima.
		int Registro::getCampoIndexante(){};

