#include <string>
#include <vector>
#include <arpa/inet.h>
#include <math.h>

#include "commonProtocolo.h"
#include "commonSocket.h"
#include "CodigosOperacion.h"


void Protocolo::recibirMapa(Socket& socket, std::string& mapa) {
	uint32_t longitud;
	socket.recibir((char *)&longitud, TAM_INT32);
	longitud = ntohl(longitud);
	mapa.resize(longitud);
	socket.recibir(&mapa[0], longitud);
	mapa[longitud] = 0;
}

void Protocolo::recibirPosiciones(Socket& socket, 
            std::unordered_map<std::string, std::pair<int, int>>& posiciones) {

	uint32_t longitud;
	socket.recibir((char *)&longitud, TAM_INT32);
	longitud = ntohl(longitud);
	posiciones.reserve(longitud);
	for (uint32_t i = 0; i < longitud; ++i) {
		std::string id_temp;
		id_temp.resize(TAM_ID);
		socket.recibir(&id_temp[0], TAM_ID);
		id_temp[TAM_ID - 1] = 0;
		float x;
		float y;
		socket.recibir((char *) &x, TAM_INT32);
		x = (float) ntohl(x);
		socket.recibir((char *) &y, TAM_INT32);
		y = (float) ntohl(y);
		std::string id(id_temp.c_str());
		posiciones[id] = { std::round(x), std::round(y) };
	}
}

void Protocolo::enviarID(Socket& socket, std::string id) {
	uint32_t operacion = CODIGO_ID;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	id.resize(TAM_ID);
	socket.enviar((char *) &id[0], TAM_ID);
}

void Protocolo::enviarChat(Socket& socket, std::string& origen,
	std::string& destino, std::string& mensaje){
	uint32_t operacion = CODIGO_MENSAJE_CHAT;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	enviarString(socket, origen);
	enviarString(socket, destino);
	enviarString(socket, mensaje);
}

void Protocolo::recibirChat(Socket& socket, std::string& mensaje,
     bool& mensaje_publico){
	recibirString(socket, mensaje);
	socket.recibir((char*) &mensaje_publico, 1);
}

void Protocolo::enviarMovimiento(Socket& socket, uint32_t movimiento) {
	uint32_t operacion = CODIGO_MOVIMIENTO;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	movimiento = htonl(movimiento);
	socket.enviar((char *) &movimiento, TAM_INT32);
}

void Protocolo::enviarString(Socket& socket_comunicacion, const std::string& string){
		uint32_t tam = string.size();
		tam = htobe32(tam);
		socket_comunicacion.enviar((char*)&tam, TAM_ENCABEZADO_STRING);
		socket_comunicacion.enviar(string.c_str(), string.size());
}

void Protocolo::recibirString(Socket& socket_comunicacion, std::string& string){
		uint32_t tam;
		std::vector<char> buffer;
		socket_comunicacion.recibir((char*)&tam, TAM_ENCABEZADO_STRING);
		tam =  be32toh(tam);
		buffer.resize(tam);
		socket_comunicacion.recibir(buffer.data(), tam);
		string.assign(buffer.data(), tam);
}

void Protocolo::enviarNumero(Socket& socket_comunicacion, uint16_t n){
	n = htobe16(n);
	socket_comunicacion.enviar((char*)&n, TAM_NUMERO);
}

uint16_t Protocolo::recibirNumero(Socket& socket_comunicacion){
	char buffer[sizeof(uint16_t)];
	uint16_t* temp;
	socket_comunicacion.recibir(buffer, TAM_NUMERO);
	temp = (uint16_t*)buffer;
	return be16toh(*temp);
}
