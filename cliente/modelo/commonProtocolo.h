#ifndef __PROTOCOLO_ADIVINA_NUMERO_H__
#define __PROTOCOLO_ADIVINA_NUMERO_H__

#include <string>
#include <cstdlib>

class Socket;

/*
*	Conjunto de métodos y definiciones relacionados al intercambio de datos
*	entre servidor-cliente y al tratamiento de los numeros.
*/

#define TAM_NUMERO 2
#define TAM_ENCABEZADO_STRING 4

void enviarString(Socket& socket_comunicacion, const std::string& string);

void recibirString(Socket& socket_comunicacion, std::string& string);

void enviarNumero(Socket& socket_comunicacion, uint16_t n);

uint16_t recibirNumero(Socket& socket_comunicacion);

#endif /*__PROTOCOLO_ADIVINA_NUMERO_H__*/
