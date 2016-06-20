#include <iostream>
#include <string>

#ifndef _REGISTRO_H
#define _REGISTRO_H

// Falta hacer el override del operador de igualdad y desigualdad.

class Registro{

	// Atributos
	private:
		
		static int campoIndexante;
		
		unsigned int id;
		std::string codigo;
		std::string descripcion;
		

	// Metodos
	public:
	
		Registro(int id, std::string codigo, std::string descripcion);

		unsigned int getID();
		void setID(unsigned int nuevoID);

		std::string getCodigo();
		void setCodigo(std::string nuevoCodigo);

		std::string getDescripcion();
		void setDescripcion(std::string nuevaDescripcion);

		int getCampoIndexante(); // Vuela!
		
		static void setCampoIndexante(int campoIndexante);
		
		bool operator==(const Registro&);
		bool operator!=(const Registro&);
		
		bool operator<(const Registro&);
		bool operator>(const Registro&);
		
		bool operator<=(const Registro&);
		bool operator>=(const Registro&);

};

#endif // REGISTRO_H
