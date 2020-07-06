#include "Cliente.h"
#include "OrganizadorClientes.h"
#include "Divulgador.h"

#include <iostream> //DEBUG

Cliente::Cliente(Socket &&socket,
                 OrganizadorSalas &unOrganizadorSalas,
                 OrganizadorClientes &organizadorClientes,
                 BaseDeDatos &unaBaseDeDatos,
                 Divulgador& divulgador) : 
                 personaje(nullptr),
                 id(""),
                 clienteProxy(std::move(socket), this, divulgador),
                 organizadorSalas(unOrganizadorSalas),
                 miBaseDeDatos(unaBaseDeDatos),
                 salaActual(""),
                 finalizado(true),
                 continuar(false){
    /*
    El id y pass del cliente se obtienen a traves de ClienteProxy, con ellos se accede a BaseDeDatos.
    El id de la sala y toda la informacion del personaje se obtiene con
    la base de datos.
    */

    // id = "jugador";
   
    std::pair<std::string, std::string> credenciales = std::move(login(organizadorClientes));
    std::pair<std::string, std::unique_ptr<Personaje>> datos = miBaseDeDatos.recuperarInformacion(credenciales);
    this->id = credenciales.first;
    this->personaje = std::move(datos.second);
    this->salaActual = std::move(datos.first);

    //Con la info recuperada de la base de datos creo un Personaje
    //Esto hay que sacarlo una vez este hecha la base de datos
    salaActual = "mapa";
    std::string idRaza = "Humano";
    std::string idClase = "Paladin";
    personaje = std::unique_ptr<Personaje> (new Personaje(100, 100, credenciales.first, idClase, idRaza));
    //Hasta aca
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

void Cliente::nuevoUsuario(std::pair<std::string, std::string> &credenciales, 
                           std::string &idRaza, 
                           std::string &idClase){
    Configuraciones *config = config->obtenerInstancia();

    std::string mapaDefault = config->obtenerMapaInicial();
    std::pair<float, float> pos = config->obtenerMapaPosicionSpawn(mapaDefault);
    Personaje nuevoPersonaje(pos.first, pos.second, id, idClase, idRaza);
    //Debe lanzar error si ya esta en uso.
    miBaseDeDatos.nuevoCliente(credenciales, mapaDefault, &nuevoPersonaje);
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
    return personaje.get();
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

std::pair<std::string, std::string> Cliente::login(OrganizadorClientes &organizador){
    std::pair<std::string, std::string> credenciales;
    bool login_establecido = false;
    while (!login_establecido){
        credenciales = clienteProxy.recibirId();
        while (organizador.idEnUso(credenciales.first)){
            clienteProxy.enviarError("Error: El id que ha ingresado ya ha sido logueado.");
            credenciales = clienteProxy.recibirId();
        }
        if (miBaseDeDatos.idExistente(credenciales)){
            login_establecido = true;
        }else{
            clienteProxy.enviarError("Error: La cuenta a la que ha intentado ingresar es inexistente.");
        }
    }
    
    clienteProxy.enviarMensajeConfirmacion();
    return credenciales;
}