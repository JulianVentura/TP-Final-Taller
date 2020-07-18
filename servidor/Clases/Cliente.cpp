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
                 finalizado(false),
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

    Sala* miSala = organizadorSalas.obtenerSala(salaActual);
    ColaOperaciones *colaDeOperaciones = miSala->obtenerCola();
    clienteProxy.actualizarCola(colaDeOperaciones);
    
    miSala->cargarCliente(this);
    continuar = true;
    clienteProxy.enviarConfirmacion();
    this->enviarInventario();
}

void Cliente::nuevoUsuario(std::pair<std::string, std::string> &credenciales, 
                           std::string &idRaza, 
                           std::string &idClase){
    Configuraciones *config = config->obtenerInstancia();
    salaActual = config->obtenerMapaInicial();
    std::pair<float, float> pos = config->obtenerMapaPosicionSpawn(salaActual);
    auto personaje = std::unique_ptr<Personaje> (new Personaje(pos.first, pos.second,
    credenciales.first, idClase, idRaza));
    personaje -> recibirOro(10000);
    miBaseDeDatos.nuevoCliente(credenciales, idRaza, idClase,
    salaActual, personaje.get());
}


void Cliente::actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones,
                               const std::vector<SerializacionDibujado> &dibujado){
    try{
        clienteProxy.enviarEstado(std::move(personaje->serializarEstado()));
        clienteProxy.enviarDibujadoPersonajes(dibujado);
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

void Cliente::enviarContenedor(const SerializacionContenedor &&serContenedor){
    clienteProxy.enviarContenedor(std::move(serContenedor));
}

void Cliente::enviarTienda(const SerializacionContenedor &&serContenedor){
    clienteProxy.enviarTienda(std::move(serContenedor));
}

void Cliente::enviarInventario(){
    clienteProxy.enviarInventario(std::move(personaje->serializarEquipo()));
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
            }else{
                if(miBaseDeDatos.verificarFormato(credenciales)){
                    clienteProxy.enviarError("Error: Usuario y/o clave incorrectos");
                }else{
                    clienteProxy.enviarError("Error: Se prohiben espacios, @ y #."
                        " La cantidad de letras no debe superar 19");
                }
            }
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
