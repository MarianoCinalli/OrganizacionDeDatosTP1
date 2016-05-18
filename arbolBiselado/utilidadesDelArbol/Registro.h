#ifndef _REGISTRO_H
#define _REGISTRO_H
#include <iostream>
#include <string>
using namespace std;
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
		Registro(string campoIndexante);

		unsigned int getID();
		void setID(unsigned int nuevoID);

		int getCodigo();
		void setCodigo(int nuevoCodigo);

		string getDescripcion();
		void setDescripcion(string nuevaDescripcion);

		int getCampoIndexante();

};

#endif // REGISTRO_H
