#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <functional>
#include <utility>

#include "commonSocket.h"

Socket::Socket(){
	file_descriptor = -1;
}

Socket::Socket(int file_descriptor) : file_descriptor(file_descriptor){}

Socket::~Socket(){
	if(file_descriptor < 0) return;
	close(file_descriptor);
	file_descriptor = -1;
}


Socket::Socket(Socket&& otro){
	file_descriptor = otro.file_descriptor;
	otro.file_descriptor = -1;
}

Socket& Socket::operator= (Socket&& otro){
	if (this == &otro) return *this;
	if (file_descriptor > 0) close(file_descriptor);
	file_descriptor = otro.file_descriptor;
	otro.file_descriptor = -1;
	return *this;
}

/*
*	Itera sobre las direcciones vinculadas al host y servicio señalados e
*	intenta aplicar "funcion" sobre ellas. De lograrlo, devuelve 0, de lo
*	contrario ERROR_CONEXION.
*/
static int _iterarDirecciones(int& file_descriptor, const char* dir,
	const char* servicio, struct addrinfo* hints,
	std::function<int(int, const struct sockaddr*, socklen_t)> funcion){
	bool funcion_exitosa = false;
	struct addrinfo *dir_posibles;
	if (getaddrinfo(dir, servicio, hints, &dir_posibles)) return ERROR_CONEXION;

	for (struct addrinfo *dir_actual = dir_posibles;
		dir_actual != NULL && funcion_exitosa == false;
		dir_actual = dir_actual->ai_next) {
		file_descriptor = socket(dir_actual->ai_family, 
			dir_actual->ai_socktype, dir_actual->ai_protocol);
	if (file_descriptor == -1) continue;

	funcion_exitosa = (funcion(file_descriptor, dir_actual->ai_addr, 
		dir_actual->ai_addrlen) != -1);
	if (!funcion_exitosa) close(file_descriptor);
}

freeaddrinfo(dir_posibles);
return (funcion_exitosa) ? 0 : ERROR_CONEXION;
}

void Socket::conectar(const char* dir, const char* servicio){
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo)); 
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if(_iterarDirecciones(file_descriptor,dir,servicio,&hints,&connect)
		== ERROR_CONEXION)
		throw FallaConexionException();
}

void Socket::cerrar_canal(int canal){
	shutdown(file_descriptor, canal);
}

int Socket::enviar(const char* buffer,size_t largo){
	size_t bytes_enviados = 0;
	int retorno = 0;
	while (bytes_enviados < largo) {
		retorno = send(file_descriptor, &buffer[bytes_enviados],
			largo - bytes_enviados, MSG_NOSIGNAL);
		if(retorno  <= 0) throw FallaConexionException();
		bytes_enviados += retorno;
	}

	return retorno;
}

int Socket::recibir(char* buffer, size_t largo){
	size_t bytes_recibidos = 0;
	int retorno = 0;
	while (largo - bytes_recibidos != 0){
		retorno = recv(file_descriptor, &buffer[bytes_recibidos],
			largo - bytes_recibidos, 0);
		bytes_recibidos += retorno;
		// if(retorno <= 0) throw FallaConexionException();
	}
	return bytes_recibidos;
}

/*
*	SO_REUSEADDR debe establecerse antes de llamar a bind. Esta funcion
*	permite aprovechar _iterarDirecciones sin romper tal precondicion.
*/
static int _bindConOpciones(int sockfd, const struct sockaddr *addr,
	socklen_t addrlen){
	int opcion = 1;

	if(setsockopt(sockfd,SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),
		(char*)&opcion,sizeof(opcion)) < 0) return ERROR_CONEXION;

		return bind(sockfd,addr,addrlen);
}


void Socket::ligar(const char* servicio){
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if(_iterarDirecciones(file_descriptor,0,servicio,&hints,&_bindConOpciones)
		== ERROR_CONEXION)
		throw FallaConexionException();
}

void Socket::escuchar(int limite_de_cola){
	listen(file_descriptor, limite_de_cola);
}

Socket Socket::aceptar(){
	int retorno = accept(file_descriptor, NULL, NULL);
	if(retorno < 0) throw FallaConexionException();
	Socket socket_aceptado(retorno);
	return /*std::move*/(socket_aceptado);
}
