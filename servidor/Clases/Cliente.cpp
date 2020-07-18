#include "Cliente.h"
#include "OrganizadorClientes.h"
#include "Configuraciones.h"
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
                 continuar(false),
                 tiempoTranscurrido(0),
                 tiempoActualizacionInventario(0){
    
    Configuraciones *config = Configuraciones::obtenerInstancia();
    tiempoActualizacionInventario = config->obtenerClienteTiempoActualizacionInventario();
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
    auto personaje = std::unique_ptr<Personaje> (new Personaje(0, 
                                                               0,
                                                               credenciales.first, 
                                                               idClase, 
                                                               idRaza));
    personaje->actualizarPosicion(std::move(config->obtenerMapaPosicionSpawn(salaActual)));
    personaje -> recibirOro(1000);
    miBaseDeDatos.nuevoCliente(credenciales, idRaza, idClase,
    salaActual, personaje.get());
}


void Cliente::actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones,
                               const std::vector<SerializacionDibujado> &dibujado,
                               double tiempo){
    try{
        tiempoTranscurrido += tiempo;
        if (tiempoTranscurrido >= tiempoActualizacionInventario){
            tiempoTranscurrido = 0;
            this->enviarInventario();
        }
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
    this->cambiarDeMapa(idMapa, std::move(config->obtenerMapaPosicionSpawn(salaActual)));
}


void Cliente::cambiarDeMapa(std::string &idMapa, Posicion nuevaPos){
    Configuraciones *config = config->obtenerInstancia();
    Sala *salaDestino = organizadorSalas.obtenerSala(idMapa);
    Sala *salaOrigen = organizadorSalas.obtenerSala(salaActual);
    salaActual = idMapa;
    salaOrigen->eliminarCliente(this->id); //Se descarga y se elimina al personaje del mapa.
    personaje->actualizarPosicion(std::move(nuevaPos));
    salaDestino->cargarCliente(this);
}
