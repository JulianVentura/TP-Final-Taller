#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <atomic>
#include <vector>

#include "../../common/commonSocket.h"
#include "../../common/Serializacion.h"

#include "ClienteProxy.h"
#include "Personaje.h"
#include "OrganizadorSalas.h"

#include "Item.h"
#include "ExcepcionSocket.h"
#include "ExcepcionCliente.h"
#include "BaseDeDatos.h"
#include <memory>

class OrganizadorClientes;
class Divulgador;

class Cliente : public Thread{
    private:
    std::unique_ptr<Personaje> personaje;
    std::string id;
    ClienteProxy clienteProxy;
    OrganizadorSalas &organizadorSalas;
    BaseDeDatos &miBaseDeDatos;
    std::string salaActual;
    std::atomic<bool> finalizado;
    std::atomic<bool> continuar;
    std::pair<std::string, std::string> login(OrganizadorClientes &organizador);

    public:
    Cliente(Socket &&socket,
            OrganizadorSalas &organizadorSalas,
            OrganizadorClientes &organizadorClientes,
            BaseDeDatos &unaBaseDeDatos);
    Cliente(Cliente &&otro) = delete;
    Cliente(Cliente &otro) = delete;
    Cliente& operator=(Cliente &&otro) = delete;
    Cliente& operator=(Cliente &otro) = delete;

    void nuevoUsuario(std::pair<std::string, std::string> &credenciales, 
                      std::string &idRaza, 
                      std::string &idClase);
    std::string obtenerId();
    std::string& obtenerIdSala();
    Sala *obtenerSala();
    Personaje* obtenerPersonaje();
    
    void cambiarDeMapa(std::string &idMapa);
    void procesar();
    bool haFinalizado();

    //Envio
    void cargarMapa(const std::vector<char> &&infoMapa);
    void actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones,
                          const std::vector<struct serializacionEstado> &estados);
    void enviarMensaje(const std::string& mensaje);
    void enviarChat(const std::string& mensaje, bool mensaje_publico);
    void enviarTienda(std::vector<Item*>& items);
    void enviarContenedor(std::vector<Item*>& items);
    void enviarInventario();

    //ClienteProxy es friend de Cliente
    friend class ClienteProxy;
};

#endif
