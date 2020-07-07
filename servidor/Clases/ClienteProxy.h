#ifndef __CLIENTE_PROXY_H__
#define __CLIENTE_PROXY_H__

#include <arpa/inet.h> //Para htons
#include <vector>
#include <mutex>

#include "ColaOperaciones.h"
#include "PosicionEncapsulada.h"
#include "OperacionMover.h"
#include "ExcepcionCliente.h"
#include "Item.h"
#include "OperacionInteractuar.h"
#include "OperacionComprar.h"
#include "OperacionVender.h"

#include "../../common/commonProtocolo.h"
#include "../../common/commonSocket.h"
#include "../../common/CodigosOperacion.h"

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
    void decodificarInteraccion();
    void decodificarCompra();
    void decodificarVenta();
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
    void enviarEstadisticas();
    void enviarMensajeConfirmacion();
    void enviarConfirmacion();
    void enviarTienda(std::vector<Item*>& items);
    void enviarContenedor(std::vector<Item*>& items);
    void enviarInventario(std::vector<Item*>& items, uint16_t oro);
    void enviarEstado(uint16_t vidaActual, 
                      uint16_t vidaMaxima,
                      uint16_t manaActual, 
                      uint16_t manaMaximo,
                      uint16_t experiencia,
                      uint16_t limiteParaSubir);
};

#endif
