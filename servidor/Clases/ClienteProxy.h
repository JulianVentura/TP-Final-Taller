#ifndef __CLIENTE_PROXY_H__
#define __CLIENTE_PROXY_H__

#include <arpa/inet.h> //Para htons
#include <vector>
#include <mutex>

#include "ColaOperaciones.h"
#include "../../common/ColaBloqueanteMensajes.h"
#include "../../common/Mensaje.h"
#include "OperacionMover.h"
#include "../../common/Excepcion.h"
#include "Item.h"
#include "OperacionInteractuar.h"
#include "OperacionTransaccion.h"
#include "OperacionComprar.h"
#include "OperacionVender.h"
#include "OperacionAtacar.h"
#include "OperacionUtilizar.h"
#include "OperacionMeditar.h"
#include "OperacionResucitar.h"
#include "OperacionTirar.h"

#include "../../common/commonProtocolo.h"
#include "../../common/commonSocket.h"
#include "../../common/CodigosOperacion.h"
#include "../../common/Serializacion.h"
#include "../../common/ProxyEnviador.h"
#include "ExcepcionLogin.h"
class Divulgador;
class Cliente;
class OrganizadorClientes;
class ClienteProxy{

private:
    std::mutex m;
    Socket socket;
    Cliente *cliente;
    ColaOperaciones *colaOperaciones;
    ColaBloqueanteMensajes colaEnvio;
    ProxyEnviador enviador;
    Protocolo protocolo;
    uint32_t limiteCorte;

    /*
    Cada uno de los siguientes metodos permiten decodificar un mensaje proveniente desde el cliente.
    Tras ser decodificado se creara la operacion correspondiente, la cual sera encolada en la cola del 
    gameloop al cual el cliente pertenece.
    */

    bool decodificarCodigo(uint32_t codigo);
    void decodificarMovimiento();
    void decodificarMeditacion();
    void decodificarResucitacion();
    void decodificarMensajeChat();
    void decodificarInteraccion();
    void decodificarTransaccion();
    void decodificarCompra();
    void decodificarVenta();
    void decodificarAtaque();
    void decodificarUtilizacion();
    void decodificarTirado();
    void decodificarJugador( std::string& id, std::string& clave);
    void decodificarNuevoJugador( std::string& id, std::string& clave);

    /*
    Encola el mensaje pasado por parametro en la cola de envio.
    Si el tamaño en bytes de la cola supera el limite establecido se corta la comunicacion
    con el cliente.
    */
    void encolarMensaje(Mensaje &&mensaje);

public:
    ClienteProxy(Socket socket, Cliente *cliente);
    /*
    Actualiza la cola de operaciones sobre la cual se encolaran las operaciones
    creadas en las recepciones de mensajes.
    */
    void actualizarCola(ColaOperaciones *colaDeOperaciones);
    /*
    Finaliza el procesamiento, cerrando la conexion con el cliente y liberando a ProxyEnviador
    */
    void finalizar();
    //Recepcion
    std::pair<std::string, std::string> recibirId();
    /*
    Recibe el codigo de operacion por TCP proveniente del cliente y lo parsea.
    Se encarga de llamar al metodo de decodificacion correspondiente.
    */
    bool recibirOperacion();
    //Envio
    /*
    Los siguientes metodos se utilizan para enviar informacion al cliente por medio de TCP.
    Cada uno de estos metodos utiliza el commonProtocol para convertir los bytes a enviar.
    Tras finalizar la conversion encolan una instancia de Mensaje en la cola de envios.
    */
    void enviarPosiciones(const std::vector<struct PosicionEncapsulada> &posiciones);
    void enviarDibujadoPersonajes(const std::vector<SerializacionDibujado> &dibujados);
    void enviarInformacionMapa(const std::vector<char> &infoMapa);
    void enviarError(std::string mensaje);
    void enviarMensaje(const std::string& mensaje, bool mensaje_publico);
    void enviarEstadisticas();
    void enviarConfirmacion();
    void enviarTienda(const SerializacionContenedor &&contenedor);
    void enviarContenedor(const SerializacionContenedor &&contenedor);
    void enviarInventario(const SerializacionEquipo &&serEquipo);
    void enviarEstado(SerializacionEstado serializacionEstado);
};

#endif
