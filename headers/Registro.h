#include <iostream>
#include <string>

using namespace std;

#ifndef _REGISTRO_H
#define _REGISTRO_H

// Falta hacer el override del operador de igualdad y desigualdad.

class Registro{

	// Atributos
	private:

		unsigned int id;
		int codigo;
		string descripcion;
		static int* campoIndexante;

	// Metodos
	public:
		Registro();
		Registro(int campoIndexante);

		unsigned int getID();
		void setID(unsigned int nuevoID);

		int getCodigo();
		void setCodigo(int nuevoCodigo);

		string getDescripcion();
		void setDescripcion(string nuevaDescripcion);

        //entonces devuelve un string el campo indexante?
		int getCampoIndexante();

};

#endif // REGISTRO_H
