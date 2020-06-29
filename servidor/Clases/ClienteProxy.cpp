#include "ClienteProxy.h"
#include <arpa/inet.h> //Para htons
#include "OperacionMover.h"
#include "Cliente.h"
#include "ExcepcionCliente.h"
#define TAM_CODIGO 4
typedef enum CODIGOS{
                     CODIGO_POSICIONES,
                     CODIGO_ID,
                     CODIGO_CARGA_MAPA,
                     CODIGO_MOVIMIENTO,
                     CODIGO_MENSAJE_CHAT,
                     CODIGO_DESCONECTAR
}CodigoPosiciones_t;

ClienteProxy::ClienteProxy(Socket unSocket, Cliente *miCliente) : 
                           socket(std::move(unSocket)),
                           cliente(miCliente),
                           colaOperaciones(nullptr){}

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

void ClienteProxy::decodificarMensajeChat(){
    //Seguir el protocolo de un mensaje
    //Enviarle el mensaje al divulgador.
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
            //Se ignora el mensaje
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



void ClienteProxy::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
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
    
}
