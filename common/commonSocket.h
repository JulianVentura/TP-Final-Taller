#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <exception>
#include <cstddef>
/*
*	Clase que encapsula la administración de sockets y el intercambio de bytes
*	a través de ellos.
*/

#define ERROR_CONEXION -1

struct FallaConexionException : public std::exception {
   const char * what() const throw() {
      return "Error: Falla Conexion\n";
   }
};

class Socket{
private:
	int file_descriptor;
	
public:
	Socket();
	explicit Socket(int file_descriptor);
	Socket(Socket& otro) = delete;
	Socket(const Socket& otro) = delete;
	Socket(Socket&& otro);
	Socket& operator= (Socket&& otro);
	Socket& operator= (Socket& otro) = delete;

	/*
	*	Si surge algún inconveniente los siguientes métodos lanzan
	*	FallaConexionException.
	*/
	void conectar(const char* direccion, const char* servicio);
	void escuchar(int limite_de_cola);

	/*
	*	Cierra todo o parte de la conexion full-duplex, dependiendo
	*	del canal indicado:
	*	SHUT_RD   - Deshabilita la recepcion de datos.
	*	SHUT_WR   - Deshabilita el envío de datos.
	*	SHUT_RDWR - Deshabilita ambos canales.
	*/
	void cerrar_canal(int canal);

	/*
	*	Devuelve por movimiento el socket aceptado.
	*	Lanza FallaConexionException en caso de error.
	*/
	Socket aceptar();

	/*
	*	Retornan la cantidad de bytes enviádos/recibidos y lanzan
	*	FallaConexionException en casos adversos.
	*	Recibir se bloquea hasta que se reciban largo bytes.
	*/
	int enviar(const char* buffer,size_t largo);
	int recibir(char* buffer, size_t largo);

	void ligar(const char* servicio);
	
	~Socket();
};

#endif /*__SOCKET_H__*/
