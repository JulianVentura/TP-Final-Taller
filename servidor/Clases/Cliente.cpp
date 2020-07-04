#include "Cliente.h"
#include "OrganizadorClientes.h"
#include "Divulgador.h"

#include <iostream> //DEBUG

Cliente::Cliente(Socket &&socket,
                 OrganizadorSalas &unOrganizadorSalas,
                 OrganizadorClientes &organizadorClientes,
                 BaseDeDatos &unaBaseDeDatos,
                 Divulgador& divulgador) : 
                 personaje(0, 0, ""),
                 id(""),
                 clienteProxy(std::move(socket), this, divulgador),
                 organizadorSalas(unOrganizadorSalas),
                 miBaseDeDatos(unaBaseDeDatos),
                 salaActual(""),
                 finalizado(true),
                 continuar(false){
    /*
    El id del cliente se obtiene a traves de ClienteProxy, con el se accede a BaseDeDatos.
    El id de la sala y toda la informacion del personaje se obtiene con
    la base de datos.
    */
    id = clienteProxy.recibirId();
    //id = "jugador";
    if (organizadorClientes.idEnUso(id)){
        socket.apagar(READ_AND_WRITE);
        //Tambien se podria entrar en un bucle en el cual se reciban distintos ids, hasta que el id sea valido
        //o hasta que el Cliente envie una peticion de logout.
        clienteProxy.enviarError("Error: El id que ha ingresado ya ha sido logueado. Finaliza la conexion.");
        throw ExcepcionCliente
        ("Error: El id que se ha solicitado ya se encuentra conectado");
    }
    //miBaseDeDatos.recuperarInformacion(id);
    //Con la info recuperada de la base de datos creo un Personaje
    salaActual = "mapa1";
    personaje = Personaje(0, 0, id);
    Sala* miSala = organizadorSalas.obtenerSala(salaActual);
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

 void Cliente::enviarChat(const std::string& mensaje, bool mensaje_publico){
    clienteProxy.enviarChat(mensaje, mensaje_publico);
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
    Sala *miSala = organizadorSalas.obtenerSala(salaActual);
    miSala->eliminarCliente(id);
    clienteProxy.finalizar();
    finalizado = true;
}

bool Cliente::haFinalizado(){
    return finalizado; 
}