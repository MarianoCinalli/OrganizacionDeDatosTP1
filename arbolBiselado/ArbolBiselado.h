#ifndef _ARBOLBISELADO_H
#define _ARBOLBISELADO_H

class ArbolBiselado{

	// Atributos


	private:
	int numeroDeBloqueHijoIzquierdo;
	int numeroDeBloqueHijoDerecho;
	Nodo* hijoIzquierdo;
	Nodo* hijoDerecho;
	Lista* registros;

	// Metodos
	public:
	ArbolBiselado();

	void setNumeroDeBloqueHijoIzquierdo(int numero);
	int getNumeroDeBloqueHijoIzquierdo();

	void setNumeroDeBloqueHijoDerecho(int numero);
	int getNumeroDeBloqueHijoDerecho();

	void setHijoIzquierdo(Nodo* hijoIzquierdo);
	Nodo* getHijoIzquierdo();

	void setHijoDerecho(Nodo* hijoDerecho);
	Nodo* getHijoDerecho();
	
	void insertar(Registro* registro);
	void modificar(Registro* registro);
	void eliminar(int identificador);

	~ArbolBiselado();
};

#endif // ARBOLBISELADO_H
