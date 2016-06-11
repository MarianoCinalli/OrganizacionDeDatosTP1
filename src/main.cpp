#include<iostream>
#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Nodo.h"
#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\ArbolBiselado.h"

using namespace std;
int main(int argc, const char* argv[])
{
cout << "hola mundo";
Registro* unRegistro = new Registro();
unRegistro ->setID(16);
Registro* otroRegistro = new Registro();
otroRegistro->setID(2);
ArbolBiselado* unArbol = new ArbolBiselado();
unArbol->insertar(unRegistro);
unArbol->insertar(otroRegistro);
	return 0;

}
