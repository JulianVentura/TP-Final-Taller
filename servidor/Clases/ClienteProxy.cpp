#include "ClienteProxy.h"
#include "Divulgador.h"

#include <iostream>

#define TAM_CODIGO 4

ClienteProxy::ClienteProxy(Socket unSocket, Cliente *miCliente,
                           Divulgador& divulgador) : 
                           socket(std::move(unSocket)),
                           cliente(miCliente),
                           colaOperaciones(nullptr),
                           divulgador(divulgador){}

void ClienteProxy::finalizar(){
    socket.apagar(READ_AND_WRITE);
    socket.cerrar();
}

void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaDeOperaciones;
}

////////////////////////RECEPCION DE MENSAJES/////////////////////////

void ClienteProxy::decodificarMovimiento(){
    uint32_t direccionMovimiento = 0;
    socket.recibirMensaje((char*)&direccionMovimiento, sizeof(uint32_t));
    direccionMovimiento = ntohl(direccionMovimiento);
    Operacion *operacion = new OperacionMover(cliente->personaje.get(), (DireccionMovimiento)direccionMovimiento);
    colaOperaciones->push(operacion);
}

void _enviarString(Socket& socket_comunicacion, const std::string& string){
    uint32_t tam = string.size();
    tam = htobe32(tam);
    socket_comunicacion.enviarMensaje((char*)&tam, TAM_ENCABEZADO_STRING);
    socket_comunicacion.enviarMensaje(string.c_str(), string.size());
}

void _recibirString(Socket& socket_comunicacion, std::string& string){
    uint32_t tam;
    std::vector<char> buffer;
    socket_comunicacion.recibirMensaje((char*)&tam, TAM_ENCABEZADO_STRING);
    tam =  be32toh(tam);
    buffer.reserve(tam);
    socket_comunicacion.recibirMensaje(buffer.data(), tam);
    string.assign(buffer.data(), tam);
}

void ClienteProxy::decodificarMensajeChat(){
    std::string origen, destino, mensaje;
    _recibirString(socket, origen);
    _recibirString(socket, destino);
    _recibirString(socket, mensaje);
    divulgador.encolarMensaje(origen, destino, mensaje);
}


 void ClienteProxy::enviarChat(const std::string& mensaje, bool mensaje_publico){
    std::lock_guard<std::mutex> lock(m);
    uint32_t operacion = CODIGO_MENSAJE_CHAT;
    operacion = htonl(operacion);
    socket.enviarMensaje((char*) &operacion, TAM_INT32);
    _enviarString(socket, mensaje);
    socket.enviarMensaje((char*) &mensaje_publico, 1);
}



bool ClienteProxy::decodificarCodigo(uint32_t codigo){
    switch (codigo){
        case CODIGO_MOVIMIENTO:
            decodificarMovimiento();
            break;
        
        case CODIGO_MENSAJE_CHAT:
            decodificarMensajeChat();
            break;
        
        case CODIGO_DESCONECTAR:
            return false;
       
        default:
            enviarError("No se ha podido decodificar el codigo de operacion, finaliza la conexion");
            return false;
    }
    return true;
}


void ClienteProxy::decodificarJugador( std::string& id, std::string& clave){
    _recibirString(socket, id);
    _recibirString(socket, clave);
}

void ClienteProxy::decodificarNuevoJugador( std::string& id, std::string& clave){
    std::string raza, clase;
    decodificarJugador(id, clave);
    _recibirString(socket, id);
    std::pair<std::string, std::string> par(id, clave);
    _recibirString(socket, raza);
    _recibirString(socket, clase);
    cliente -> nuevoUsuario(par, raza, clase);
}

std::pair<std::string, std::string> ClienteProxy::recibirId(){
    std::string id, clave;
    uint32_t codigo = 0;
    socket.recibirMensaje((char*)&codigo, TAM_CODIGO);
    codigo = ntohl(codigo);
    switch (codigo){
        case CODIGO_ID:
            decodificarJugador(id, clave);
            break;
        case CODIGO_NUEVO_PERSONAJE:
            decodificarNuevoJugador(id, clave);
            break;
        case CODIGO_DESCONECTAR:
            throw ExcepcionCliente
            ("Conexion no completada por peticion del cliente");  
        default:
            enviarError("No se ha interpretado la operacion solicitada. Finaliza la conexion");
            throw ExcepcionCliente
            ("No se ha recibido el id por parte del cliente");  
    }

    return std::pair<std::string, std::string>(id, clave);
}

bool ClienteProxy::recibirOperacion(){
    uint32_t codigo = 0;
    socket.recibirMensaje((char*)&codigo, TAM_CODIGO);
    codigo = ntohl(codigo);
    return decodificarCodigo(codigo);
}

//////////////////////////ENVIO DE MENSAJES/////////////////////////////

void ClienteProxy::enviarError(std::string mensaje){
    std::lock_guard<std::mutex> lock(m);
    uint32_t codigo = CODIGO_ERROR;
    uint32_t largoMensaje = mensaje.length();
    codigo = htonl(codigo);
    largoMensaje = htonl(largoMensaje);
    socket.enviarMensaje((char*)&codigo, sizeof(codigo));
    socket.enviarMensaje((char*)&largoMensaje, sizeof(largoMensaje));
    socket.enviarMensaje(mensaje.c_str(), mensaje.length());
}

void ClienteProxy::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
    std::lock_guard<std::mutex> lock(m);
    uint32_t codigo = CODIGO_POSICIONES;
    codigo = htonl(codigo);
    socket.enviarMensaje((char*)&codigo, TAM_CODIGO);
    uint32_t largo = posiciones.size();
    largo = htonl(largo);
    socket.enviarMensaje((char*)&largo, sizeof(largo));
    for (auto &posicion : posiciones){
        socket.enviarMensaje(posicion.id, TAM_ID);
        float temp = htonl(posicion.x);
        socket.enviarMensaje((char*)&temp, sizeof(float));
        temp = htonl(posicion.y);
        socket.enviarMensaje((char*)&temp, sizeof(float));
    }
}

void ClienteProxy::enviarInformacionMapa(const std::vector<char> &infoMapa){
    std::lock_guard<std::mutex> lock(m);
    uint32_t codigo = CODIGO_CARGA_MAPA;
    uint32_t largo_mensaje = infoMapa.size();
    //Envio el codigo de operacion
    codigo = htonl(codigo);
    socket.enviarMensaje((char*)&codigo, TAM_CODIGO);
    //Envio el largo del archivo
    largo_mensaje = htonl(largo_mensaje);
    socket.enviarMensaje((char*)&largo_mensaje, sizeof(largo_mensaje));
    //Envio el archivo
    socket.enviarMensaje(infoMapa.data(), infoMapa.size());
}

void ClienteProxy::enviarMensaje(const std::string& mensaje){
    //TODO
}

void ClienteProxy::enviarMensajeConfirmacion(){
    std::lock_guard<std::mutex> lock(m);
    uint32_t codigo = CODIGO_CARGA_MAPA;
    socket.enviarMensaje((char*)&codigo, TAM_CODIGO);
}



/*

Como se transmite el estado del personaje hacia el cliente:

En cada iteracion del gameloop se debera actualizar al Cliente con el estado del personaje, esto implica enviar:

- Vida actual, vida max, mana actual, mana max, nivel actual, exp, limite exp, oro.

Ademas se le debera enviar a cada cliente la siguiente linea, para que dibuje a los personajes:

- arma, casco, escudo, armadura, raza, clase, estado.

Luego, cuando el cliente lo indique se le puede mandar info del inventario:

- vector<IdItem> //Es un vector con los ids de cada item ordenados, habra que pensar un id para casilla vacia.

*/


/*
Operaciones:

- OP_NUEVO_JUGADOR
- OP_LOGIN
- OP_LOGOUT/DESCONECTAR
- OP_INFO_JUGADOR
- OP_ABRIR_INVENTARIO
- OP_ATACAR
- OP_TOMAR
- OP_LISTAR
- OP_COMPRAR
- OP_VENDER
- OP_MEDITAR
- OP_INTERACTUAR
- OP_TIRAR

*/