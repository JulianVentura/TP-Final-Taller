#ifndef __CLIENTE_PROXY_H__
#define __CLIENTE_PROXY_H__

#include <arpa/inet.h> //Para htons
#include <vector>
#include <mutex>

#include "ColaOperaciones.h"
#include "PosicionEncapsulada.h"
#include "OperacionMover.h"
#include "ExcepcionCliente.h"

#include "../../common/commonProtocolo.h"
#include "../../common/commonSocket.h"
#include "../../common/CodigosOperacion.h"

/*
#define TAM_ENCABEZADO_STRING 4
#define TAM_INT32 4
*/
class Divulgador;
class Cliente;
class OrganizadorClientes;
class ClienteProxy{

private:
    std::mutex m;
    Socket socket;
    Cliente *cliente;
    ColaOperaciones *colaOperaciones;
    Divulgador& divulgador;
    Protocolo protocolo;
    bool decodificarCodigo(uint32_t codigo);
    void decodificarMovimiento();
    void decodificarMensajeChat();
    void decodificarJugador( std::string& id, std::string& clave);
    void decodificarNuevoJugador( std::string& id, std::string& clave);

public:
    ClienteProxy(Socket socket, Cliente *cliente, Divulgador& divulgador);
    void actualizarCola(ColaOperaciones *colaDeOperaciones);
    void finalizar();
    //Recepcion
    std::pair<std::string, std::string> recibirId();
    bool recibirOperacion();
    //Envio
    void enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones);
    void enviarInformacionMapa(const std::vector<char> &infoMapa);
    void enviarError(std::string mensaje);
    void enviarMensaje(const std::string& mensaje);
    void enviarChat(const std::string& mensaje, bool mensaje_publico);
    void enviarMensajeConfirmacion();
    void enviarConfirmacion();
};

#endif
