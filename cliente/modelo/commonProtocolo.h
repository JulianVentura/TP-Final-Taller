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
class Protocolo {
public:
    void enviarString(Socket& socket_comunicacion, const std::string& string);
    void recibirString(Socket& socket_comunicacion, std::string& string);
    void enviarNumero(Socket& socket_comunicacion, uint16_t n);
    void enviarMovimiento(Socket& socket, uint32_t movimiento);
    void enviarID(Socket& socket, std::string& id);
    uint16_t recibirNumero(Socket& socket_comunicacion);
    void recibirMensaje(Socket& socket);
    std::string obtenerMapa();
    std::vector<struct Posicionable> obtenerPosiciones();

private:
    void recibirMapa(Socket& socket);
    void recibirPosiciones(Socket& socket);
    std::string mapa;
    std::vector<struct Posicionable> posiciones;
};
#endif /*__PROTOCOLO_ADIVINA_NUMERO_H__*/
