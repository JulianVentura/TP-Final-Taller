#include <string>
#include <arpa/inet.h>
#include <math.h>

#include "commonProtocolo.h"
#include "commonSocket.h"

void Protocolo::enviarString(Socket& socket_comunicacion, const std::string& string){
	uint32_t tam = string.size();
	tam = htobe32(tam);
	mensajeActual.agregarBytes((char*)&tam, TAM_ENCABEZADO_STRING);
	mensajeActual.agregarBytes(string.c_str(), string.size());
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

void Protocolo::enviarUint8(Socket& socket_comunicacion, uint8_t n){
	mensajeActual.agregarBytes((char*)&n, TAM_INT8);
}

uint8_t Protocolo::recibirUint8(Socket& socket_comunicacion){
	char buffer;
	socket_comunicacion.recibir(&buffer, TAM_INT8);
	return buffer;
}

void Protocolo::enviarUint16(Socket& socket_comunicacion, uint16_t n){
	n = htobe16(n);
	mensajeActual.agregarBytes((char*)&n, TAM_INT16);
}

uint16_t Protocolo::recibirUint16(Socket& socket_comunicacion){
	char buffer[sizeof(uint16_t)];
	uint16_t* temp;
	socket_comunicacion.recibir(buffer, TAM_INT16);
	temp = (uint16_t*)buffer;
	return be16toh(*temp);
}

void Protocolo::enviarUint32(Socket& socket_comunicacion, uint32_t n){
	n = htobe32(n);
	mensajeActual.agregarBytes((char*)&n, TAM_INT32);
}

uint32_t Protocolo::recibirUint32(Socket& socket_comunicacion){
	char buffer[sizeof(uint32_t)];
	uint32_t* temp;
	socket_comunicacion.recibir(buffer, TAM_INT32);
	temp = (uint32_t*)buffer;
	return be32toh(*temp);
}

Mensaje Protocolo::finalizarEnvio(){
	return std::move(mensajeActual);
}
