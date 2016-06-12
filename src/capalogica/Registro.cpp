#include <string>
#include "Registro.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Registro.h"
// Metodos
Registro::Registro(int id, std::string codigo, std::string descripcion){
	
	this -> id = id;
	this -> codigo = codigo;
	this -> descripcion = descripcion;
	
};

Registro::Registro(int campoIndexante){
	
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

// Esto es poque al iniciar el arbol se elije el campo para usar como identificador.
// Si al principo te dicen que se ordena por ID aca devolves la ID, osea no usas el getID para recorrer el arbol.
// Lo mismo si se elije codigo.
// Aca hay que setear la variable estatica. El lunes lo hablamos de ultima.
int Registro::getCampoIndexante(){
	
    return id;
    
};

