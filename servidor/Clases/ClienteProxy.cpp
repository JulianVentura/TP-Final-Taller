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

void ClienteProxy::decodificarTransaccion(){
    //bool esDeposito = protocolo.recibirUint8(socket);
    //std::string id = protocolo.recibirString(socket);
    /*
    Operacion *operacion = new OperacionTransar(cliente,
    esDeposito, id);
    colaOperaciones->push(operacion);
    */
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

void ClienteProxy::decodificarMeditacion(){
    Operacion *operacion = new OperacionMeditar(cliente);
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

        case CODIGO_MEDITACION:
            decodificarMeditacion();
            break;

        case CODIGO_TRANSACCION:
            decodificarTransaccion();
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

void ClienteProxy::enviarTienda(const std::vector<SerializacionItem> &&items){
	std::lock_guard<std::mutex> lock(m);
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    for(auto item : items){
        protocolo.enviarUint16(socket, item.idTCP);
    	protocolo.enviarUint16(socket, item.precio);
    }
}

void ClienteProxy::enviarContenedor(const std::vector<SerializacionItem> &&items){
	std::lock_guard<std::mutex> lock(m);
	uint16_t cero = 0;
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    for(auto& item : items){
        protocolo.enviarUint16(socket, item.idTCP);
    	protocolo.enviarUint16(socket, cero);
    }
}

void ClienteProxy::enviarInventario(const SerializacionEquipo serEquipo){
	std::lock_guard<std::mutex> lock(m);
	protocolo.enviarUint32(socket, CODIGO_INVENTARIO);
    protocolo.enviarUint16(socket, serEquipo.armaEquipada);
    protocolo.enviarUint16(socket, serEquipo.armaduraEquipada);
    protocolo.enviarUint16(socket, serEquipo.cascoEquipado);
    protocolo.enviarUint16(socket, serEquipo.escudoEquipado);
    for(auto& serItem : serEquipo.items){
        protocolo.enviarUint16(socket, serItem.idTCP);
    }
    protocolo.enviarUint16(socket, serEquipo.oro);
}

void ClienteProxy::enviarConfirmacion(){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_CONFIRMACION);
}


void ClienteProxy::enviarEstado(SerializacionEstado serEstado){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ESTADISTICAS);
    protocolo.enviarUint16(socket, serEstado.vidaActual);
    protocolo.enviarUint16(socket, serEstado.vidaMaxima);
    protocolo.enviarUint16(socket, serEstado.manaActual);
    protocolo.enviarUint16(socket, serEstado.manaMaximo);
    protocolo.enviarUint16(socket, serEstado.experiencia);
    protocolo.enviarUint16(socket, serEstado.limiteParaSubir);
    protocolo.enviarUint32(socket, serEstado.nivel);
}

void ClienteProxy::enviarDibujadoPersonajes(const std::vector<SerializacionDibujado> &dibujados){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ESTADOS);
    uint32_t largo = dibujados.size();
    protocolo.enviarUint32(socket, largo);
    for (auto &dibujado : dibujados){
        socket.enviar(dibujado.id, TAM_ID);
        protocolo.enviarUint16(socket, dibujado.idArmaEquipada);
        protocolo.enviarUint16(socket, dibujado.idArmaduraEquipada);
        protocolo.enviarUint16(socket, dibujado.idCascoEquipado);
        protocolo.enviarUint16(socket, dibujado.idEscudoEquipado);
        protocolo.enviarUint16(socket, dibujado.idRaza);
        protocolo.enviarUint16(socket, dibujado.idClase);
        protocolo.enviarUint16(socket, dibujado.idEstado);
    }
}
