#ifndef _REGISTRO_H
#define _REGISTRO_H

template <class T>
class Registro{

	// Atributos
	private:
		// No estoy seguro de los tipos de las variables segun el tp tenian que ser:
		unsigned int id;    // 4 bytes 
		int codigo;         // 3 bytes. Supongo que al momento de persistir operamos con bits para hacerlos ocupar menos.
		String descripcion; 

	// Metodos
	public:
		unsigned int getID();
		void setID(unsigned int nuevoID);

		int getCodigo();
		void setCodigo(int nuevoCodigo);	
	
		String getDescripcion();
		void setDescripcion(String nuevaDescripcion);

		// Esto es poque al iniciar el arbol se elije el campo para usar como identificador. 
		// Si al principo te dicen que se ordena por ID aca devolves la ID, osea no usas el getID para recorrer el arbol.
		// Lo mismo si se elije codigo.
		// Aca hay que setear la variable estatica. El lunes lo hablamos de ultima.
		int getCampoIndexante();

};

#endif // REGISTRO_H
