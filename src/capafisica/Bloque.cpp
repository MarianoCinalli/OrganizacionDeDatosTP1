#include "Bloque.h"
//#include "C:\CSV\TpDatos\OrganizacionDeDatosTP1\headers\Bloque.h"
// Constructor para la escritura de un nodo en disco.
Bloque::Bloque(Nodo* nodo) {

    int hijoIzquierdoEntero = nodo -> getNumeroDeBloqueHijoIzquierdo();
    int hijoDerechoEntero = nodo -> getNumeroDeBloqueHijoDerecho();

    this -> hijoIzquierdo = transformarEnteroAString(hijoIzquierdoEntero, 2);
    this -> hijoDerecho = transformarEnteroAString(hijoDerechoEntero, 2);

    this -> numeroDeBloque = nodo -> getNumeroDeBloque();

    transformarRegistros( nodo -> getListaDeRegistros());

};

// Constructor para carga desde el disco.
Bloque::Bloque(std::string bloqueComoString, unsigned int numeroDeBloque) {

    this -> numeroDeBloque = numeroDeBloque;

    recuperarInformacion(bloqueComoString);

}

// Para poder escribir en disco concatena toda la informacion en un string
std::string Bloque::exportarParaEscritura() {

    std::string bloque;

    bloque = armarBloque();

    return (bloque);

};

// Encapsula la informacion del bloque en la clase nodo.
Nodo* Bloque::exportarComoNodo() {

    int hijoDerecho = transformarStringAEntero(this -> hijoDerecho);
    int hijoIzquierdo = transformarStringAEntero( this -> hijoIzquierdo);

    Lista <Registro*>* listaDeRegistros = tansformarStringDeRegistrosAListaDeRegistros();

	// Veo si el nodo es hoja.
	bool esHoja = false;
    if (hijoDerecho == 0 && hijoIzquierdo == 0) esHoja = true;

    Nodo* nodo = new Nodo(hijoDerecho, listaDeRegistros, hijoIzquierdo, this -> numeroDeBloque, esHoja);

    return (nodo);

}

// Si el bloque no tiene registros devuelve true.
// False en caso contrario.
bool Bloque::bloqueSinRegistros(){

	return ( registros.length() == 0 );

}

int Bloque::getNumeroDeBloque() {

    return ( this -> numeroDeBloque);

}

// Metodos privados ----------------------------------------------------

// Armado de registros -------------------------------------------------

// Coloca en un string el contenido de cada registro perteneciente a la lista.

void Bloque::transformarRegistros(Lista<Registro*>* listaDeRegistros) {

    listaDeRegistros -> iniciarCursor();

    // Lista de objectos registro -> string con registos
    while (listaDeRegistros -> avanzarCursor()) {

        Registro* registroActual = listaDeRegistros -> obtenerCursor();
        std::string registroActualEnString = registroAString(registroActual);
        registros += registroActualEnString;

    }

};

// Transforma un objeto registro en un string.
// Se agrega como prefijo el tamanio de la informacion en el string.
// Estructura registros
// Tamanio del registro - Id - Codigo - Descripcion
std::string Bloque::registroAString(Registro* registro) {

    // Obtengo cada campo.
    unsigned int id = registro -> getID();
    string codigo = registro -> getCodigo();
    std::string descripcion = registro -> getDescripcion();

    // Transformo ID string.
    std::string stringID = transformarEnteroAString(id, 4);

    // Concateno los campos.
    std::string camposConcatenados = stringID + codigo + descripcion;

    // Obtengo el tamanio de los campos concatenados.
    int tamanio = camposConcatenados.length();
    // Con dos bytes alcanza.
    // Maximo = id + codigo + descripcion = 4 + 3 + 1000 = 1007
    std::string stringTamanio = transformarEnteroAString(tamanio, 2);

    // Concateno con el tamanio.
    return ( stringTamanio + camposConcatenados);

};

// Divide un numero en partes, los hace chars y los concatena
// en un string que devuelve. En la posicion 0 el MSB.

std::string Bloque::transformarEnteroAString(unsigned int entero,unsigned int cantidadDeBytes) {
    std::string stringADevolver = "";

    unsigned int parte;
    unsigned char parteChar;

    // Se procesa desde el byte menos al mas significativo.
    for (unsigned int i = 0; i < cantidadDeBytes; i++) {
        parte = entero >> (i * 8);
        parteChar = (char) parte;
        stringADevolver += parteChar;
    }

    return (stringADevolver);

};

// Armado del bloque ---------------------------------------------------

// Crea una representacion del bloque como string.
// Siguiendo el siguiente patron.
// Estructura del bloque
// Tamanio del bloque - NB hijo izquierdo - registros - NB hijo derecho

std::string Bloque::armarBloque() {

    // Variables.
    string bloque;
    std::string stringDeDatos;
    std::string stringTamanio;
    unsigned int tamanio;
    // Fin variables.

    // hijo izquierdo + registros
    stringDeDatos += this -> hijoIzquierdo;
    stringDeDatos += this -> registros;

    // (hijo izquierdo + registros) + hijo derecho
    stringDeDatos += this -> hijoDerecho;

    // calculo el tamanio
    tamanio = stringDeDatos.length();

    // Si el tamanio del bloque es mayor que el el maximo tamanio disponible
    // para datos. Tiro una excepcion.
    if( MAXIMO_TAMANIO_DE_DATOS < tamanio )throw ElNodoExcedeElTamanioMaximo();

    // tamanio a string
    stringTamanio = transformarEnteroAString(tamanio, 2);

    // stringTamanio + (hijo izquierdo + registros + hijo derecho)
    bloque += stringTamanio;
    bloque += stringDeDatos;

    return (bloque);

};

// Armado del nodo -----------------------------------------------------

void Bloque::recuperarInformacion(std::string informacion) {

    // Recupero la longitud de la informacion del nodo en el string.
    int longitud = recuperarLongitud(informacion);

    // Saco el campo con la longitud y la basura que queda luego
    // del ultimo dato valido del string, para dejar los datos.
    // Observar que longitud en este caso es el largo del string
    // que voy a crear a continuacion.
    std::string datos = informacion.substr(2, longitud);

    // En las posiciones 0 y 1 esta el hijo izquierdo.
    this -> hijoIzquierdo = datos.substr(0, 2);

    // En las posiciones 2 hasta (longitud - 2) estan los registros.
    // Es -4 porque son longitud - 4 caracteres desde la posicion 2.
    this -> registros = datos.substr(2, longitud - 4);

    // En las posiciones (longitud - 1) y longitud estan los registros.
    this -> hijoDerecho = datos.substr(longitud - 2, 2);

}

// Del bloque recuperado del disco, separa el tamanio de la informacion
// en el y lo devuelve.

int Bloque::recuperarLongitud(std::string cadena) {

    std::string longitudEnString = cadena.substr(0, 2);

    return ( transformarStringAEntero(longitudEnString));

}

// Antitransformada de entero a string.

unsigned int Bloque::transformarStringAEntero(std::string cadena) {
    // Variables
    unsigned int transformado = 0;
    unsigned int valorActual;
    unsigned char caracterActual;
    unsigned int longitudDeLaCadena = cadena.length();
    // El primero del string es el LSB
    // La posicion en el array * 8 es la cantidad de shifts a hacer.
    for (unsigned int i = 0; longitudDeLaCadena > i; i++) {
        // char to int
        caracterActual = cadena[i];
        valorActual = (unsigned int) caracterActual;
        // shift
        valorActual <<= (i * 8);
        transformado = transformado + valorActual;
    }

    return (transformado);

}

// Por cada registro guardado en el string, uno a continuacion
// del otro, arma un objeto Registro y lo coloca en la lista.

Lista<Registro*>* Bloque::tansformarStringDeRegistrosAListaDeRegistros() {

    Lista<Registro*>* listaDeRegistros = new Lista<Registro*>;

    int posicion = 0;
    int tamanioDelStringDeRegistros = this -> registros.length();

    // Armo por cada registro en el string un objeto registro y lo pongo el la pila.
    while (posicion < tamanioDelStringDeRegistros) {

        // Registro = Tamanio (ID + codigo + descripcion)- ID - Codigo - Descripcion
        // En Bytes =    2                                 4      3      tamanio - 7
        int finalDeRegistro = transformarStringAEntero(registros.substr(posicion, 2));

        std::string registroActual = registros.substr(posicion + 2, finalDeRegistro);

        int id = transformarStringAEntero(registroActual.substr(0, 4));

        std::string codigo = registroActual.substr(4, 3);

        std::string descripcion = registroActual.substr(7, (finalDeRegistro-7));

        Registro* registro = new Registro(id, codigo, descripcion);
        listaDeRegistros -> agregar(registro);

        // Sumo lo que ocupaba el tamanio y el finalDeRegistro.
        posicion += 2;
        posicion += finalDeRegistro;

    }

    return (listaDeRegistros);

}
