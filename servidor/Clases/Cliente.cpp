#include "Cliente.h"
#include "OrganizadorClientes.h"
#include "Divulgador.h"

#include <iostream> //DEBUG

Cliente::Cliente(Socket &&socket,
                 OrganizadorSalas &unOrganizadorSalas,
                 OrganizadorClientes &organizadorClientes,
                 BaseDeDatos &unaBaseDeDatos) : 
                 personaje(nullptr),
                 id(""),
                 clienteProxy(std::move(socket), this),
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
    
    std::pair<std::string, std::string> credenciales =
     std::move(login(organizadorClientes));
    std::pair<std::string, std::unique_ptr<Personaje>> datos =
     miBaseDeDatos.cargarCliente(credenciales);
    this->id = credenciales.first;
    this->personaje = std::move(datos.second);
    this->salaActual = std::move(datos.first);

    /*******************************************************************
    * Franco, no me borres esto hasta que la base no ande por favor.   *
    *                                                                  *
    *                                                                  *
    ********************************************************************/
    //Desde aca.
    /*
    salaActual = "mapa";
    std::string idRaza = "Humano";
    std::string idClase = "Paladin";
    personaje = std::unique_ptr<Personaje> (new Personaje(600, 600, credenciales.first, idClase, idRaza));
    personaje -> recibirOro(1000);
    */
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
    clienteProxy.enviarConfirmacion();
}

void Cliente::nuevoUsuario(std::pair<std::string, std::string> &credenciales, 
                           std::string &idRaza, 
                           std::string &idClase){
    Configuraciones *config = config->obtenerInstancia();
    salaActual = config->obtenerMapaInicial();
    std::pair<float, float> pos = config->obtenerMapaPosicionSpawn(salaActual);
    auto personaje = std::unique_ptr<Personaje> (new Personaje(pos.first, pos.second,
    credenciales.first, idClase, idRaza));
    personaje -> recibirOro(1000);
    miBaseDeDatos.nuevoCliente(credenciales, idRaza, idClase,
    salaActual, personaje.get());
   
    /*
    if(!miBaseDeDatos.existeCliente(credenciales.first)){
        
    }else{
        clienteProxy.enviarError("Error: Ya existe la cuenta solicitada");
    }
    */
}


void Cliente::actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones,
                               const std::vector<struct serializacionEstado> &estados){
    try{
        clienteProxy.enviarEstado(personaje->vidaActual,
                                  personaje->vidaMaxima,
                                  personaje->manaActual,
                                  personaje->manaMaximo,
                                  personaje->experiencia,
                                  personaje->limiteParaSubir);
        enviarInventario();       //Refinar más adelante
        clienteProxy.enviarEstadosPersonajes(estados);
        clienteProxy.enviarPosiciones(posiciones);
    }catch(...){
        //Cualquier error es motivo suficiente como para cortar
        // la comunicacion con el Cliente
        continuar = false;
    }
}  

 void Cliente::enviarMensaje(const std::string& mensaje){
    //clienteProxy.enviarMensaje(mensaje);
 }

 void Cliente::enviarChat(const std::string& mensaje, bool mensaje_publico){
    clienteProxy.enviarChat(mensaje, mensaje_publico);
}

void Cliente::enviarContenedor(std::vector<Item*>& items){
    clienteProxy.enviarContenedor(items);
}

void Cliente::enviarTienda(std::vector<Item*>& items){
    clienteProxy.enviarTienda(items);
}

void Cliente::enviarInventario(){
    clienteProxy.enviarInventario(*personaje -> obtenerInventario(),
     personaje -> obtenerOro());
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

Sala *Cliente::obtenerSala(){
    return this->organizadorSalas.obtenerSala(salaActual);
}

std::string& Cliente::obtenerIdSala(){
    return salaActual;
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
    miBaseDeDatos.guardarCliente(this);
    clienteProxy.finalizar();
    finalizado = true;
}

bool Cliente::haFinalizado(){
    return finalizado; 
}

std::pair<std::string, std::string> Cliente::login(OrganizadorClientes &organizador){
    std::pair<std::string, std::string> credenciales;
    while (true){
        credenciales = clienteProxy.recibirId();
        if(organizador.idEnUso(credenciales.first)){
            clienteProxy.enviarError
            ("Error: El id que ha ingresado ya ha sido logueado");
            credenciales = clienteProxy.recibirId();
        }else{
            if (miBaseDeDatos.verificarCliente(credenciales)){
                return credenciales;
            }
            
            clienteProxy.enviarError("Error: Usuario y/o clave incorrectos");
        }
    }
}

void Cliente::cambiarDeMapa(std::string &idMapa){
    Configuraciones *config = config->obtenerInstancia();
    Sala *salaDestino = organizadorSalas.obtenerSala(idMapa);
    Sala *salaOrigen = organizadorSalas.obtenerSala(salaActual);
    salaOrigen->eliminarCliente(this->id); //Se descarga y se elimina al personaje del mapa.
    std::pair<float, float> pos = config->obtenerMapaPosicionSpawn(salaActual);
    Posicion posicion(pos.first, pos.second, 0,0);
    personaje->actualizarPosicion(std::move(posicion)); //Tambien se podria directamente obtener un Posicion de configuraciones.
    salaDestino->cargarCliente(this);
}
