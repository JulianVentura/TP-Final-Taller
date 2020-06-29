#include <string>
#include <vector>

#include "commonProtocolo.h"
#include "commonSocket.h"

void enviarString(Socket& socket_comunicacion, const std::string& string){
		uint32_t tam = string.size();
		tam = htobe32(tam);
		socket_comunicacion.enviar((char*)&tam, TAM_ENCABEZADO_STRING);
		socket_comunicacion.enviar(string.c_str(), string.size());
}

void recibirString(Socket& socket_comunicacion, std::string& string){
		uint32_t tam;
		std::vector<char> buffer;
		socket_comunicacion.recibir((char*)&tam, TAM_ENCABEZADO_STRING);
		tam =  be32toh(tam);
		buffer.reserve(tam);
		socket_comunicacion.recibir(buffer.data(), tam);
		string.assign(buffer.data(), tam);
}

void enviarNumero(Socket& socket_comunicacion, uint16_t n){
	n = htobe16(n);
	socket_comunicacion.enviar((char*)&n, TAM_NUMERO);
}

uint16_t recibirNumero(Socket& socket_comunicacion){
	char buffer[sizeof(uint16_t)];
	uint16_t* temp;
	socket_comunicacion.recibir(buffer, TAM_NUMERO);
	temp = (uint16_t*)buffer;
	return be16toh(*temp);
}