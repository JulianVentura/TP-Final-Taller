#include <string>
#include <vector>
#include <arpa/inet.h>
#include <math.h>

#include "commonProtocolo.h"
#include "commonSocket.h"
#include "../../common/CodigosOperacion.h"
#define TAM_INT32 4
#define TAM_ID 20 // TODO: podría estar en common/CodigosOperacion o algo por el 
				  // estilo.

// TODO: RC maybe
void Protocolo::recibirMapa(Socket& socket) {
	uint32_t longitud;
	socket.recibir((char *)&longitud, TAM_INT32);
	longitud = ntohl(longitud);
	mapa.reserve(longitud);
	socket.recibir(&mapa[0], longitud);
	mapa[longitud] = 0;
}

// TODO: RC maybe
void Protocolo::recibirPosiciones(Socket& socket) {
	std::vector<Posicionable> posiciones_temp;
	uint32_t longitud;
	socket.recibir((char *)&longitud, TAM_INT32);
	longitud = ntohl(longitud);
	posiciones_temp.reserve(longitud);
	for (uint32_t i = 0; i < longitud; ++i) {
		std::string id;
		id.reserve(TAM_ID);
		socket.recibir(&id[0], TAM_ID);
		id[TAM_ID - 1] = 0;
		float x;
		float y;
		socket.recibir((char *) &x, TAM_INT32);
		x = (float) ntohl(x);
		socket.recibir((char *) &y, TAM_INT32);
		y = (float) ntohl(y);
		struct Posicionable posicion = {};
		posicion.id = std::move(id);
		posicion.x = std::round(x);
		posicion.y = std::round(y);
		posiciones_temp.push_back(posicion);
	}
	this->posiciones = std::move(posiciones_temp);
}
void Protocolo::enviarID(Socket& socket, std::string& id) {
	uint32_t operacion = CODIGO_ID;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	id.resize(TAM_ID);
	socket.enviar((char *) &id[0], TAM_ID);
}

void Protocolo::enviarMovimiento(Socket& socket, uint32_t movimiento) {
	uint32_t operacion = CODIGO_MOVIMIENTO;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	movimiento = htonl(movimiento);
	socket.enviar((char *) &movimiento, TAM_INT32);
}

void Protocolo::recibirMensaje(Socket& socket) {
	uint32_t operacion;
	socket.recibir((char *)&operacion, TAM_INT32);
	operacion = ntohl(operacion);
	switch (operacion) {
		case CODIGO_CARGA_MAPA:
			recibirMapa(socket);
			break;
		
		case CODIGO_POSICIONES:
			recibirPosiciones(socket);

			break;
		case CODIGO_MENSAJE_CHAT: // TODO: no estoy seguro la dirección de este
			printf("Chat\n");
			break;
		default:
			printf("No reconocido %d\n", operacion);
			break;
	}
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
		buffer.reserve(tam);
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

// TODO: RC maybe
std::string Protocolo::obtenerMapa() {
	return std::move(mapa);
}

std::vector<struct Posicionable> Protocolo::obtenerPosiciones() {
	return std::move(posiciones);
}
