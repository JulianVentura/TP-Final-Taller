#ifndef __CLIENTE_PROXY_H__
#define __CLIENTE_PROXY_H__
#include "Socket.h"
#include "ColaOperaciones.h"
#include "PosicionEncapsulada.h"
#include <vector>

class Cliente;
class ClienteProxy{
    private:
    Socket socket;
    Cliente *cliente;
    ColaOperaciones *colaOperaciones;
    bool decodificarCodigo(uint32_t codigo);
    void decodificarMovimiento();
    void decodificarMensajeChat();
    public:
    ClienteProxy(Socket socket, Cliente *cliente);
    void actualizarCola(ColaOperaciones *colaDeOperaciones);
    void finalizar();
    //Recepcion
    std::string recibirId();
    bool recibirOperacion();
    //Envio
    void enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones);
    void enviarInformacionMapa(const std::vector<char> &infoMapa);
    void enviarError(std::string mensaje);
    void enviarMensaje(const std::string& mensaje);
};

#endif
