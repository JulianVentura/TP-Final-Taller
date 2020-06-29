#include "ClienteProxy.h"
#include <arpa/inet.h> //Para htons
#include "OperacionMover.h"
#include "Cliente.h"
#define TAM_CODIGO 4
typedef enum CODIGOS{
                     CODIGO_POSICIONES,
                     CODIGO_ID,
                     CODIGO_CARGA_MAPA,
                     CODIGO_MOVIMIENTO,
                     CODIGO_MENSAJE_CHAT,
}CodigoPosiciones_t;

ClienteProxy::ClienteProxy(Socket unSocket, Cliente *miCliente) : 
                           socket(std::move(unSocket)),
                           cliente(miCliente),
                           colaOperaciones(nullptr){}


void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaOperaciones;
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


void ClienteProxy::decodificarCodigo(uint32_t codigo){
    switch (codigo){
        case CODIGO_MOVIMIENTO:{
            decodificarMovimiento();
            break;
        }
        case CODIGO_MENSAJE_CHAT:{
            decodificarMensajeChat();
            break;
        }
        default: {
            /*
            Se pueden hacer varias cosas:
            1- Enviarle un mensaje al cliente indicando que tiene que reenviar el id.
            2- Lanzar una excepcion, lo que implica destruir la conexion con el cliente.
            3- Devolver una excepcion particular y que Cliente decida si quiere reintentar.
            */
        }  
    }
}


std::string ClienteProxy::recibirId(){
    uint32_t codigo = 0;
    char id_buffer[TAM_ID] = {0};
    socket.recibirMensaje((char*)&codigo, TAM_CODIGO);
    codigo = ntohl(codigo);
    if (codigo != CODIGO_ID){
        /*
        Se pueden hacer varias cosas:
        1- Enviarle un mensaje al cliente indicando que tiene que reenviar el id.
        2- Lanzar una excepcion, lo que implica destruir la conexion con el cliente.
        3- Devolver una excepcion particular y que Cliente decida si quiere reintentar.
        */   
    }
    socket.recibirMensaje(id_buffer, TAM_ID);
    return std::string(id_buffer);
}

void ClienteProxy::recibirOperacion(){
    uint32_t codigo = 0;
    socket.recibirMensaje((char*)&codigo, TAM_CODIGO);
    codigo = ntohl(codigo);
    decodificarCodigo(codigo);
}

//////////////////////////ENVIO DE MENSAJES/////////////////////////////



void ClienteProxy::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
    uint32_t codigo = CODIGO_POSICIONES;
    codigo = htonl(codigo);
    socket.enviarMensaje((char*)&codigo, TAM_CODIGO);
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
