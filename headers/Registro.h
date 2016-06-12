#include <iostream>
#include <string>

#ifndef _REGISTRO_H
#define _REGISTRO_H

// Falta hacer el override del operador de igualdad y desigualdad.

class Registro{

	// Atributos
	private:

		unsigned int id;
		std::string codigo;
		std::string descripcion;
		static int* campoIndexante;

	// Metodos
	public:
		Registro(int id, std::string codigo, std::string descripcion);
		Registro(int campoIndexante);

		unsigned int getID();
		void setID(unsigned int nuevoID);

		std::string getCodigo();
		void setCodigo(std::string nuevoCodigo);

		std::string getDescripcion();
		void setDescripcion(std::string nuevaDescripcion);

        //entonces devuelve un string el campo indexante?
		int getCampoIndexante();

};

#endif // REGISTRO_H
