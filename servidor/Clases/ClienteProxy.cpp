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
    socket.cerrar_canal(SHUT_RDWR);
}

void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaDeOperaciones;
}

////////////////////////RECEPCION DE MENSAJES/////////////////////////

void ClienteProxy::decodificarMovimiento(){
    /*
    uint32_t direccionMovimiento = 0;
    socket.recibirMensaje((char*)&direccionMovimiento, sizeof(uint32_t));
    direccionMovimiento = ntohl(direccionMovimiento);
*/
    uint32_t direccionMovimiento = protocolo.recibirUint32(socket);
    Operacion *operacion = new OperacionMover(cliente->personaje.get(),
     (DireccionMovimiento)direccionMovimiento);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarMensajeChat(){
    std::string origen, destino, mensaje;
    protocolo.recibirString(socket, origen);
    protocolo.recibirString(socket, destino);
    protocolo.recibirString(socket, mensaje);
    divulgador.encolarMensaje(origen, destino, mensaje);
}

void ClienteProxy::enviarChat(const std::string& mensaje, bool mensaje_publico){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_MENSAJE_CHAT);
    protocolo.enviarString(socket, mensaje);
    socket.enviar((char*) &mensaje_publico, 1);
}

void ClienteProxy::decodificarInteraccion(){
    std::string id;
    protocolo.recibirString(socket, id);
    Operacion *operacion = new OperacionInteractuar(cliente,
     cliente -> obtenerSala() -> obtenerMapa(), id);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarCompra(){
    std::string id;
    protocolo.recibirString(socket, id);
    uint16_t  pos = protocolo.recibirUint16(socket);
    Operacion *operacion = new OperacionComprar(cliente,
    cliente -> obtenerSala() -> obtenerMapa(), pos, id);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarVenta(){
    std::string id;
    protocolo.recibirString(socket, id);
    uint16_t  pos = protocolo.recibirUint16(socket);
    Operacion *operacion = new OperacionVender(cliente,
    cliente -> obtenerSala() -> obtenerMapa(), pos, id);
    colaOperaciones->push(operacion);
}

bool ClienteProxy::decodificarCodigo(uint32_t codigo){
    switch (codigo){
        case CODIGO_INTERACCION:
            decodificarInteraccion();
            break;

        case CODIGO_COMPRA:
            decodificarCompra();
            break;

        case CODIGO_MOVIMIENTO:
            decodificarMovimiento();
            break;
        
        case CODIGO_MENSAJE_CHAT:
            decodificarMensajeChat();
            break;
        
        case CODIGO_VENTA:
            decodificarVenta();
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
    protocolo.recibirString(socket, id);
    protocolo.recibirString(socket, clave);
}

void ClienteProxy::decodificarNuevoJugador( std::string& id, std::string& clave){
    std::string raza, clase;
    decodificarJugador(id, clave);
    std::pair<std::string, std::string> par(id, clave);
    protocolo.recibirString(socket, raza);
    protocolo.recibirString(socket, clase);
    cliente -> nuevoUsuario(par, raza, clase);
}

std::pair<std::string, std::string> ClienteProxy::recibirId(){
    std::string id, clave;
    uint32_t codigo = protocolo.recibirUint32(socket);

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
            enviarError("No se ha interpretado la operacion solicitada.Finaliza la conexion");
            throw ExcepcionCliente
            ("No se ha recibido el id por parte del cliente");  
    }

    return std::pair<std::string, std::string>(id, clave);
}

bool ClienteProxy::recibirOperacion(){
    return decodificarCodigo(protocolo.recibirUint32(socket));
}

//////////////////////////ENVIO DE MENSAJES/////////////////////////////

void ClienteProxy::enviarError(std::string mensaje){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ERROR);
    protocolo.enviarString(socket, mensaje);
}

void ClienteProxy::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_POSICIONES);
    uint32_t largo = posiciones.size();
    largo = htonl(largo);
    socket.enviar((char*)&largo, sizeof(largo));
    for (auto &posicion : posiciones){
        socket.enviar(posicion.id, TAM_ID);
        float temp = htonl(posicion.x);
        socket.enviar((char*)&temp, sizeof(float));
        temp = htonl(posicion.y);
        socket.enviar((char*)&temp, sizeof(float));
    }
}

void ClienteProxy::enviarInformacionMapa(const std::vector<char> &infoMapa){
    std::lock_guard<std::mutex> lock(m);
    std::string mapa(infoMapa.begin(), infoMapa.end());
    protocolo.enviarUint32(socket, CODIGO_CARGA_MAPA);
    protocolo.enviarString(socket, mapa);
    /*
    uint32_t largo_mensaje = infoMapa.size();
    //Envio el largo del archivo
    largo_mensaje = htonl(largo_mensaje);
    socket.enviar((char*)&largo_mensaje, sizeof(largo_mensaje));
    //Envio el archivo
    socket.enviar(infoMapa.data(), infoMapa.size());
    */
}

void ClienteProxy::enviarTienda(std::vector<Item*>& items){
	std::lock_guard<std::mutex> lock(m);
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    uint16_t noHayItem = 0;
    for(auto item : items){
        if (item != nullptr){
            std::cerr << "Envio item";
            protocolo.enviarUint16(socket, item -> obtenerIDTCP());
    	    protocolo.enviarUint16(socket, item -> obtenerPrecio());
        }else{
            protocolo.enviarUint16(socket, noHayItem);
    	    protocolo.enviarUint16(socket, noHayItem);
        }
    }
}

void ClienteProxy::enviarContenedor(std::vector<Item*>& items){
	std::lock_guard<std::mutex> lock(m);
	uint16_t cero = 0;
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    for(auto& item : items){
    	if (item != nullptr){
            protocolo.enviarUint16(socket, item -> obtenerIDTCP());
    	    protocolo.enviarUint16(socket, cero);
        }else{
            protocolo.enviarUint16(socket, cero);
    	    protocolo.enviarUint16(socket, cero);
        }
    }
}

void ClienteProxy::enviarInventario(std::vector<Item*>& items, uint16_t oro){
	std::lock_guard<std::mutex> lock(m);
    uint16_t cero = 0;
	protocolo.enviarUint32(socket, CODIGO_INVENTARIO);
    for(auto& item : items){
    	if (item != nullptr){
            protocolo.enviarUint16(socket, item -> obtenerIDTCP());
        }else{
            protocolo.enviarUint16(socket, cero);
        }
    }
    protocolo.enviarUint16(socket, oro);
}

void ClienteProxy::enviarConfirmacion(){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_CONFIRMACION);
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