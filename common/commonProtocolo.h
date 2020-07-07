#ifndef __PROTOCOLO_ADIVINA_NUMERO_H__
#define __PROTOCOLO_ADIVINA_NUMERO_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_map>

class Socket;

/*
*	Conjunto de métodos y definiciones relacionados al intercambio de datos
*	entre servidor-cliente.
*/

#define TAM_INT16 2
#define TAM_INT32 4
#define TAM_ENCABEZADO_STRING 4
                  
class Protocolo {
public:
    void enviarString(Socket& socket_comunicacion, const std::string& string);
    void recibirString(Socket& socket_comunicacion, std::string& string);

    void enviarUint32(Socket& socket_comunicacion, uint32_t op);
    uint32_t recibirUint32(Socket& socket_comunicacion);

    void enviarUint16(Socket& socket_comunicacion, uint16_t n);
    uint16_t recibirUint16(Socket& socket_comunicacion);
};
#endif /*__PROTOCOLO_ADIVINA_NUMERO_H__*/
