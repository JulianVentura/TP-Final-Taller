#ifndef __PROTOCOLO_H__
#define __PROTOCOLO_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "Mensaje.h"

class Socket;

/*
*	Conjunto de métodos y definiciones relacionados al intercambio de datos
*	entre servidor-cliente.
*/
#define TAM_INT8  1
#define TAM_INT16 2
#define TAM_INT32 4
#define TAM_ENCABEZADO_STRING 4
#define TAM_ID 20
         
class Protocolo {
private:
    Mensaje mensajeActual;
public:
    void enviarString(Socket& socket_comunicacion, const std::string& string);
    void recibirString(Socket& socket_comunicacion, std::string& string);

	void enviarUint8(Socket& socket_comunicacion, uint8_t n);
	uint8_t recibirUint8(Socket& socket_comunicacion);

    void enviarUint32(Socket& socket_comunicacion, uint32_t n);
    uint32_t recibirUint32(Socket& socket_comunicacion);

    void enviarUint16(Socket& socket_comunicacion, uint16_t n);
    uint16_t recibirUint16(Socket& socket_comunicacion);

    Mensaje finalizarEnvio();
};
#endif /*__PROTOCOLO_H__*/
