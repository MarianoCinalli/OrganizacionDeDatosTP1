#include <iostream>
#include <string>
#include "Registro.h"
#include "Nodo.h"
#include "funcionesDePersistencia.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\ArbolBiselado.h"

using namespace std;
int main(int argc, const char* argv[]){
	
	Archivo* archivo = new Archivo("ejemploDeArbolOrdenadoPorCodigo.txt");
	
	// Raiz
	Registro* registro1= new Registro(300,"r3A","Buena Descripcion1");
	Registro* registro2= new Registro(309,"Sd2","Buena Descripcion2");
	Lista<Registro*>* registros = new Lista<Registro*>;
    Nodo* raiz = new Nodo(3, registros, 4, 2, false);
    raiz -> agregarRegistro(registro1);
    raiz -> agregarRegistro(registro2);
    
    persistirRaiz(raiz);	
	
	// Hijo izquierdo de la raiz.
	Registro* registro3= new Registro(200,"apa","Buena Descripcion3");
	Registro* registro4= new Registro(210,"opa","Buena Descripcion4");
	Lista<Registro*>* registros2 = new Lista<Registro*>;
    Nodo* hijoIzquierdo = new Nodo(0, registros2, 0, 3, true);
    hijoIzquierdo -> agregarRegistro(registro3);
    hijoIzquierdo -> agregarRegistro(registro4);
	
	persistir(hijoIzquierdo);
	
	// Hijo derecho de la raiz.
	Registro* registro5= new Registro(400,"asc","Buena Descripcion5");
	Registro* registro6= new Registro(420,"o12","Buena Descripcion6");
	Registro* registro7= new Registro(450,"x2a","Buena Descripcion7");
	Lista<Registro*>* registros3 = new Lista<Registro*>;
    Nodo* hijoDerecho = new Nodo(0, registros3, 0, 4, true);
    hijoDerecho -> agregarRegistro(registro5);
    hijoDerecho -> agregarRegistro(registro6);
    hijoDerecho -> agregarRegistro(registro7);
    
    persistir(hijoDerecho);
    
    delete (raiz);
    delete (hijoIzquierdo);
    delete (hijoDerecho);
    delete (archivo);
}
/*
	Archivo* archivo = new Archivo("archivinio.txt");
	///
	Nodo* nodito = archivo -> leerRaiz();
	Lista<Registro*>* lista = nodito -> getListaDeRegistros();
	
	lista -> iniciarCursor();
	lista -> avanzarCursor();
	Registro* registro = lista -> obtenerCursor();
	std::cout << registro -> getID() << "\n";
	std::cout << registro -> getCodigo() << "\n";
	std::cout << registro -> getDescripcion() << "\n";
	std::cout << "\n";
	
	lista -> avanzarCursor();
	Registro* registro2 = lista -> obtenerCursor();
	std::cout << registro2 -> getID() << "\n";
	std::cout << registro2 -> getCodigo() << "\n";
	std::cout << registro2 -> getDescripcion() << "\n";
	std::cout << "\n";
	
	
	delete (nodito);
	///
	
	Registro* registro1= new Registro(303,"opa","Buena Descripcion3");
	Registro* registro2= new Registro(290,"opo","Buena Descripcion1");
	Lista<Registro*>* registros = new Lista<Registro*>;
    Nodo* raiz1 = new Nodo(1000, registros, 60, 5, true);
    raiz1 -> agregarRegistro(registro1);
    raiz1 -> agregarRegistro(registro2);
    
    persistirRaiz(raiz1);
    
    Registro* registro3= new Registro(400,"a92","Buena Descripcion");
    Registro* registro4= new Registro(124,"a92","Buena Descripcion");
    Registro* registro5= new Registro(2000,"a92","Buena Descripcion");
    Lista<Registro*>* registros2 = new Lista<Registro*>;
    Nodo* raiz2 = new Nodo(320, registros2, 300, 4, true);
    raiz2 -> agregarRegistro(registro3);
    raiz2 -> agregarRegistro(registro4);
    raiz2 -> agregarRegistro(registro5);
    
    delete (raiz1);
    delete (raiz2);
    
	delete (archivo);
*/
