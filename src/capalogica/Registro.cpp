#include <string>
#include "Registro.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Registro.h"

int Registro::campoIndexante = 0;

// Metodos
Registro::Registro(int id, std::string codigo, std::string descripcion){
	
	this -> id = id;
	this -> codigo = codigo;
	this -> descripcion = descripcion;
	
};

unsigned int Registro::getID(){
	
    return id;
    
};

void Registro::setID(unsigned int nuevoID){
	
    id = nuevoID;
    
};

std::string Registro::getCodigo(){
	
    return codigo;
    
};

void Registro::setCodigo(std::string nuevoCodigo){
	
    codigo = nuevoCodigo;
    
};

std::string Registro::getDescripcion(){
	
    return descripcion;
    
};

void Registro::setDescripcion(std::string nuevaDescripcion){
    descripcion = nuevaDescripcion;
};

// Esto vuela al carajo.
int Registro::getCampoIndexante(){
	
    return id;
    
};

// si campoIndexante = 0 => el arbol se ordena por id
// si campoIndexante = 1 => el arbol se ordena por codigo
// El valor por defecto es 0.
void Registro::setCampoIndexante(int campoIndexante){
	
	campoIndexante = campoIndexante;
	
};

// Sobrecarga de operadores --------------------------------------------

bool Registro::operator== (const Registro& otro){
	
	if ( this -> campoIndexante == 0 ) return (id == otro.id);
	if ( this -> campoIndexante == 1 ) return (codigo == otro.codigo);
    
}

bool Registro::operator!= (const Registro& otro){

    return !(*this == otro);
    
}

bool Registro::operator< (const Registro& otro){
	
	if ( this -> campoIndexante == 0 ) return (id < otro.id) && (*this != otro);
	if ( this -> campoIndexante == 1 ) return (codigo < otro.codigo) && (*this != otro);
	
}

bool Registro::operator> (const Registro& otro){
	
	return !(*this < otro);
	
}

bool Registro::operator<= (const Registro& otro){
	
	return ( *this < otro || *this == otro);
	
}

bool Registro::operator>= (const Registro& otro){

	return ( *this > otro || *this == otro);
	
}
