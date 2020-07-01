#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <atomic>
#include <vector>


#include "ClienteProxy.h"
#include "Personaje.h"
#include "OrganizadorSalas.h"

#include "ExcepcionSocket.h"
#include "ExcepcionCliente.h"
#include "Socket.h"
#include "BaseDeDatos.h"
#include "PosicionEncapsulada.h"

class OrganizadorClientes;
class Divulgador;

class Cliente : public Thread{
    private:
    Personaje personaje;
    std::string id;
    ClienteProxy clienteProxy;
    OrganizadorSalas &organizadorSalas;
    BaseDeDatos &miBaseDeDatos;
    std::atomic<bool> finalizado;
    std::atomic<bool> continuar;

    public:
    Cliente(Socket &&socket,
            OrganizadorSalas &organizadorSalas,
            OrganizadorClientes &organizadorClientes,
            BaseDeDatos &unaBaseDeDatos,
            Divulgador& divulgador);
    Cliente(Cliente &&otro) = delete;
    Cliente(Cliente &otro) = delete;
    Cliente& operator=(Cliente &&otro) = delete;
    Cliente& operator=(Cliente &otro) = delete;

    std::string obtenerId();
    Personaje* obtenerPersonaje();
    void cargarMapa(const std::vector<char> &&infoMapa);
    void procesar();
    bool haFinalizado();

    //Envio
    void actualizarEstado(const std::vector<struct PosicionEncapsulada>
     &posiciones);
    void enviarMensaje(const std::string& mensaje);
    void enviarChat(const std::string& mensaje, bool mensaje_publico);

    //ClienteProxy es friend de Cliente
    friend class ClienteProxy;
};

#endif
