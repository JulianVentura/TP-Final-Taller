#include "ClienteProxy.h"
#include "Divulgador.h"

#include <iostream>

#define TAM_CODIGO 4

ClienteProxy::ClienteProxy(Socket unSocket, Cliente *miCliente) : 
                           socket(std::move(unSocket)),
                           cliente(miCliente),
                           colaOperaciones(nullptr),
                           enviador(socket, colaEnvio){
    enviador.comenzar();
}

void ClienteProxy::finalizar(){
    socket.cerrar_canal(SHUT_RDWR);
    colaEnvio.cerrarCola();
    enviador.recuperar();
}

void ClienteProxy::actualizarCola(ColaOperaciones *colaDeOperaciones){
    this->colaOperaciones = colaDeOperaciones;
}

////////////////////////RECEPCION DE MENSAJES/////////////////////////

void ClienteProxy::decodificarMovimiento(){
    uint32_t direccionMovimiento = protocolo.recibirUint32(socket);
    Operacion *operacion = new OperacionMover(cliente->obtenerPersonaje(),
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
    bool esDeposito = protocolo.recibirUint8(socket);
    std::string id;
    protocolo.recibirString(socket, id);
    Operacion *operacion = new OperacionTransaccion(cliente, 
        cliente -> obtenerSala() -> obtenerMapa(), id, esDeposito);
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

void ClienteProxy::decodificarMeditacion(){
    Operacion *operacion = new OperacionMeditar(cliente);
    colaOperaciones->push(operacion);
}

void ClienteProxy::decodificarResucitacion(){
    Operacion *operacion = new OperacionResucitar(cliente,
        cliente -> obtenerSala() -> obtenerMapa());
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

        case CODIGO_RESUCITACION:
            decodificarResucitacion();
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
        default:
            enviarError("Error: No se ha interpretado la operacion solicitada. "
                "Finaliza la conexion");
            throw Excepcion
            ("No se ha recibido el id por parte del cliente");  
    }

    return std::pair<std::string, std::string>(id, clave);
}

bool ClienteProxy::recibirOperacion(){
    return decodificarCodigo(protocolo.recibirUint32(socket));
}

//////////////////////////ENVIO DE MENSAJES/////////////////////////////

void ClienteProxy::enviarMensaje(const std::string& mensaje, bool mensaje_publico){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_MENSAJE_CHAT);
    protocolo.enviarString(socket, mensaje);
    protocolo.enviarUint8(socket, mensaje_publico);
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarError(std::string mensaje){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ERROR);
    protocolo.enviarString(socket, mensaje);
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones){
    std::lock_guard<std::mutex> lock(m);
    std::string id;
    protocolo.enviarUint32(socket, CODIGO_POSICIONES);
    protocolo.enviarUint32(socket, posiciones.size());
    for (auto &posicion : posiciones){
        id.assign(posicion.id);
        protocolo.enviarString(socket, posicion.id);
        protocolo.enviarUint32(socket, std::round(posicion.x));
        protocolo.enviarUint32(socket, std::round(posicion.y));
    }
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarInformacionMapa(const std::vector<char> &infoMapa){
    std::lock_guard<std::mutex> lock(m);
    std::string mapa(infoMapa.begin(), infoMapa.end());
    protocolo.enviarUint32(socket, CODIGO_CARGA_MAPA);
    protocolo.enviarString(socket, mapa);
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarTienda(const SerializacionContenedor &&contenedor){
	std::lock_guard<std::mutex> lock(m);
    uint16_t cero = 0;
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    protocolo.enviarUint16(socket, cero);
    for(auto item : contenedor.items){
        protocolo.enviarUint16(socket, item.idTCP);
    	protocolo.enviarUint16(socket, item.precio);
    }
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarContenedor(const SerializacionContenedor &&contenedor){
	std::lock_guard<std::mutex> lock(m);
	uint16_t cero = 0;
	protocolo.enviarUint32(socket, CODIGO_TIENDA);
    protocolo.enviarUint16(socket, contenedor.oroContenedor);
    for(auto& item : contenedor.items){
        protocolo.enviarUint16(socket, item.idTCP);
    	protocolo.enviarUint16(socket, cero);
    }
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarInventario(const SerializacionEquipo &&serEquipo){
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
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarConfirmacion(){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_CONFIRMACION);
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
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
    protocolo.enviarUint16(socket, serEstado.limiteExpInferior);
    protocolo.enviarUint32(socket, serEstado.nivel);
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ClienteProxy::enviarDibujadoPersonajes(const std::vector<SerializacionDibujado> &dibujados){
    std::lock_guard<std::mutex> lock(m);
    protocolo.enviarUint32(socket, CODIGO_ESTADOS);
    protocolo.enviarUint32(socket, dibujados.size());
    for (auto &dibujado : dibujados){
        std::string id(dibujado.id);
        protocolo.enviarString(socket, id);
        protocolo.enviarUint16(socket, dibujado.idArmaEquipada);
        protocolo.enviarUint16(socket, dibujado.idArmaduraEquipada);
        protocolo.enviarUint16(socket, dibujado.idCascoEquipado);
        protocolo.enviarUint16(socket, dibujado.idEscudoEquipado);
        protocolo.enviarUint16(socket, dibujado.idRaza);
        protocolo.enviarUint16(socket, dibujado.idClase);
        protocolo.enviarUint16(socket, dibujado.idEstado);
    }
    encolarMensaje(std::move(protocolo.finalizarEnvio()));
}


void ClienteProxy::encolarMensaje(Mensaje &&mensaje){
    try{
        if(enviador.envioBloqueado()){
            this -> finalizar();
        }else{
            colaEnvio.push(std::move(mensaje));
        }
    }catch(...){
        //Cualquier error es motivo suficiente como para cortar la comunicacion.
        this->finalizar();
    }
}   
