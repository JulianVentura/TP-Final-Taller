#ifndef __PROTOCOLO_ADIVINA_NUMERO_H__
#define __PROTOCOLO_ADIVINA_NUMERO_H__

#include <string>
#include <cstdlib>
#include <vector>

class Socket;

struct Posicionable {
    std::string id;
    int x;
    int y;
};

/*
*	Conjunto de métodos y definiciones relacionados al intercambio de datos
*	entre servidor-cliente y al tratamiento de los numeros.
*/

#define TAM_NUMERO 2
#define TAM_ENCABEZADO_STRING 4
#define TAM_INT32 4
#define TAM_ID 20 // TODO: podría estar en common/CodigosOperacion o algo por el 
                  // estilo.
                  
class Protocolo {
public:
    void enviarString(Socket& socket_comunicacion, const std::string& string);
    void recibirString(Socket& socket_comunicacion, std::string& string);
    void enviarNumero(Socket& socket_comunicacion, uint16_t n);
    void enviarMovimiento(Socket& socket, uint32_t movimiento);
    void enviarID(Socket& socket, std::string& id);
    uint16_t recibirNumero(Socket& socket_comunicacion);
    std::string obtenerMapa();
    void enviarChat(Socket& socket, std::string& origen,
    std::string& destino, std::string& mensaje);
    void recibirChat(Socket& socket, std::string& mensaje,
     bool& mensaje_publico);
    std::vector<struct Posicionable> obtenerPosiciones();

    void recibirMapa(Socket& socket);
    void recibirPosiciones(Socket& socket);

    std::string mapa;
    std::vector<struct Posicionable> posiciones;
};
#endif /*__PROTOCOLO_ADIVINA_NUMERO_H__*/
