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
    socket.apagar(SHUT_RDWR);
    socket.cerrar();
}

void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaDeOperaciones;
}

////////////////////////RECEPCION DE MENSAJES/////////////////////////

void ClienteProxy::decodificarMovimiento(){
    //Seguir el protocolo de una operacion de movimiento.
    //Crear la operacion de movimiento y luego encolar en la cola de operaciones
    uint32_t direccionMovimiento = 0;
    socket.recibirMensaje((char*)&direccionMovimiento, sizeof(uint32_t));
    direccionMovimiento = ntohl(direccionMovimiento);
    Operacion *operacion = new OperacionMover(&(cliente->personaje), (DireccionMovimiento)direccionMovimiento);
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
        case CODIGO_MOVIMIENTO:{
            decodificarMovimiento();
            break;
        }
        case CODIGO_MENSAJE_CHAT:{
            decodificarMensajeChat();
            break;
        }
        case CODIGO_DESCONECTAR:
            return false;
        default: {
            enviarError("No se ha podido decodificar el codigo de operacion, finaliza la conexion");
            return false;
        }  
    }
    return true;
}


std::string ClienteProxy::recibirId(){
    uint32_t codigo = 0;
    char id_buffer[TAM_ID] = {0};
    socket.recibirMensaje((char*)&codigo, TAM_CODIGO);
    codigo = ntohl(codigo);
    if (codigo != CODIGO_ID){
        enviarError("No se ha recibido el id del usuario");
        throw ExcepcionCliente
        ("No se ha recibido el id por parte del cliente");   
    }
    socket.recibirMensaje(id_buffer, TAM_ID);
    return std::string(id_buffer);
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
