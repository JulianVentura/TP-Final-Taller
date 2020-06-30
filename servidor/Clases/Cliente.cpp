#include "Cliente.h"
#include "OrganizadorClientes.h"
#include "ExcepcionSocket.h"
#include "ExcepcionCliente.h"
#include <iostream> //DEBUG

Cliente::Cliente(Socket &&socket,
                 OrganizadorSalas &unOrganizadorSalas,
                 OrganizadorClientes &organizadorClientes,
                 BaseDeDatos &unaBaseDeDatos) : 
                 personaje(0, 0, ""),
                 id(""),
                 clienteProxy(std::move(socket), this),
                 organizadorSalas(unOrganizadorSalas),
                 miBaseDeDatos(unaBaseDeDatos),
                 finalizado(true),
                 continuar(false){
    /*
    El id del cliente se obtiene a traves de ClienteProxy, con el se accede a BaseDeDatos.
    El id de la sala y toda la informacion del personaje se obtiene con
    la base de datos.
    */
    //id = clienteProxy.recibirId();
    id = "jugador";
    if (organizadorClientes.idEnUso(id)){
        socket.apagar(READ_AND_WRITE);
        //TODO: Avisarle al cliente que le pego un tiro
        throw ExcepcionCliente
        ("Error: El id que se ha solicitado ya se encuentra conectado");
    }
    //miBaseDeDatos.recuperarInformacion(id);
    //Con la info recuperada de la base de datos creo un Personaje
    personaje = Personaje(30, 30, id);
    Sala* miSala = organizadorSalas.obtenerSala("mapa1");
    ColaOperaciones *colaDeOperaciones = miSala->obtenerCola();
    clienteProxy.actualizarCola(colaDeOperaciones);
    //TODO:
    //clienteProxy.enviarDatosPersonaje();
    //
    miSala->cargarCliente(this);
    finalizado = false;
    continuar = true;
}

void Cliente::actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones){
    try{
        //clienteProxy.enviarEstado() Aca se envia el estado del personaje, vida, mana, exp, etc.
        clienteProxy.enviarPosiciones(posiciones);
    }catch(...){
        //Cualquier error es motivo suficiente como para cortar la comunicacion con el Cliente
        continuar = false;
    }
}  

 void Cliente::enviarMensaje(const std::string& mensaje){
    clienteProxy.enviarMensaje(mensaje);
 }

void Cliente::cargarMapa(const std::vector<char> &&infoMapa){
    try{
        clienteProxy.enviarInformacionMapa(infoMapa);
    }catch(...){
        //Cualquier error es motivo suficiente como para cortar la comunicacion con el Cliente
        continuar = false;
    }
}

std::string Cliente::obtenerId(){
    return this->id;
}
Personaje* Cliente::obtenerPersonaje(){
    return &personaje;
}

void Cliente::procesar(){
    try{
        while(continuar){
            continuar = clienteProxy.recibirOperacion();
        }
    }catch(const ExcepcionSocket &e){
        //No me interesa reportar un error de socket, no aporta nada.
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido capturado en Cliente" << std::endl;
    }
    //Liberar recursos, guardar los datos en BaseDeDatos.
    Sala *miSala = organizadorSalas.obtenerSala("mapa1");
    miSala->eliminarCliente(id);
    clienteProxy.finalizar();
    finalizado = true;
}

bool Cliente::haFinalizado(){
    return finalizado; 
}