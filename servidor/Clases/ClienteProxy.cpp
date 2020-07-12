#include "ClienteProxy.h"
#include "Divulgador.h"

#include <iostream>

#define TAM_CODIGO 4

ClienteProxy::ClienteProxy(Socket unSocket, Cliente *miCliente) : 
                           socket(std::move(unSocket)),
                           cliente(miCliente),
                           colaOperaciones(nullptr){}

void ClienteProxy::finalizar(){
    socket.cerrar_canal(SHUT_RDWR);
}

void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaDeOperaciones;
}

////////////////////////RECEPCION DE MENSAJES/////////////////////////

void ClienteProxy::decodificarMovimiento(){
    uint32_t direccionMovimiento = protocolo.recibirUint32(socket);
    Operacion *operacion = new OperacionMover(cliente->personaje.get(),
     (DireccionMovimiento)direccionMovimiento);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarMensajeChat(){
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    std::string origen, destino, mensaje;
    protocolo.recibirString(socket, origen);
    protocolo.recibirString(socket, destino);
    protocolo.recibirString(socket, mensaje);
    divulgador->encolarMensaje(origen, destino, mensaje);
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

void ClienteProxy::decodificarAtaque(){
    std::string id;
    protocolo.recibirString(socket, id);
    Operacion *operacion = new OperacionAtacar(cliente,
    cliente -> obtenerSala() -> obtenerMapa(), id);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarUtilizacion(){
    uint16_t pos = protocolo.recibirUint16(socket);
    Operacion *operacion = new OperacionUtilizar(cliente, pos);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarTirado(){
    uint16_t pos = protocolo.recibirUint16(socket);
    Operacion *operacion = new OperacionTirar(cliente, pos);
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
       
        case CODIGO_UTILIZACION:
            decodificarUtilizacion();
            break;

        case CODIGO_TIRADO:
            decodificarTirado();
            break;

        case CODIGO_ATAQUE:
            decodificarAtaque();
            break;

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
            enviarError("No se ha interpretado la operacion solicitada. "
                "Finaliza la conexion");
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
}

void ClienteProxy::enviarTienda(std::vector<Item*>& items){
	std::lock_guard<std::mutex> lock(m);
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    uint16_t noHayItem = 0;
    for(auto item : items){
        if (item != nullptr){
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


void ClienteProxy::enviarEstado(uint16_t vidaActual, 
                                uint16_t vidaMaxima,
                                uint16_t manaActual, 
                                uint16_t manaMaximo,
                                uint16_t experiencia,
                                uint16_t limiteParaSubir){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ESTADISTICAS);
    protocolo.enviarUint16(socket, vidaActual);
    protocolo.enviarUint16(socket, vidaMaxima);
    protocolo.enviarUint16(socket, manaActual);
    protocolo.enviarUint16(socket, manaMaximo);
    protocolo.enviarUint16(socket, experiencia);
    protocolo.enviarUint16(socket, limiteParaSubir);
}

