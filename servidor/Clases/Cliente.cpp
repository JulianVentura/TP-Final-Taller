#include "Cliente.h"
#include <iostream> //DEBUG

Cliente::Cliente(Socket &&socket,
                 OrganizadorSalas &unOrganizadorSalas,
                 BaseDeDatos &unaBaseDeDatos) : 
                 personaje(0, 0, ""),
                 id(""),
                 clienteProxy(std::move(socket), this),
                 organizadorSalas(unOrganizadorSalas),
                 miBaseDeDatos(unaBaseDeDatos),
                 finalizado(false){
    /*
    El id del cliente se obtiene a traves de ClienteProxy, con el se accede a BaseDeDatos.
    El id de la sala y toda la informacion del personaje se obtiene con
    la base de datos.
    */
    id = clienteProxy.recibirId();
    //miBaseDeDatos.recuperarInformacion(id);
    //Con la info recuperada de la base de datos creo un Personaje
    personaje = Personaje(0, 0, id);
    Sala* miSala = organizadorSalas.obtenerSala("mapa1");
    miSala->cargarCliente(this);
    ColaOperaciones *colaDeOperaciones = miSala->obtenerCola();
    clienteProxy.actualizarCola(colaDeOperaciones);
}

void Cliente::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
    clienteProxy.enviarPosiciones(posiciones);
}  

void Cliente::cargarMapa(const std::vector<char> &&infoMapa){
    clienteProxy.enviarInformacionMapa(infoMapa);
}

std::string Cliente::obtenerId(){
    return this->id;
}
Personaje* Cliente::obtenerPersonaje(){
    return &personaje;
}

void Cliente::procesar(){
    bool continuar = true;
    while(continuar){
        //continuar = clienteProxy.recibirMensaje();
    }
    //Liberar recursos
    finalizado = true;
}

bool Cliente::haFinalizado(){
    return finalizado; 
}