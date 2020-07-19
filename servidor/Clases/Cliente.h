#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <atomic>
#include <vector>

#include "../../common/commonSocket.h"
#include "../../common/Serializacion.h"

#include "ClienteProxy.h"
#include "Personaje.h"
#include "OrganizadorSalas.h"

#include "Item.h"
#include "Excepcion.h"
#include "BaseDeDatos.h"
#include <memory>

class OrganizadorClientes;
class Divulgador;

class Cliente : public Thread{
    private:
    std::unique_ptr<Personaje> personaje;
    std::string id;
    ClienteProxy clienteProxy;
    OrganizadorSalas &organizadorSalas;
    BaseDeDatos &miBaseDeDatos;
    std::string salaActual;
    std::atomic<bool> finalizado;
    std::atomic<bool> continuar;
    double tiempoTranscurrido;
    double tiempoActualizacionInventario;
    /*
    Ejecuta la operacion de login de un cliente.
    Permite de esta forma comprobar la validez de un usuario y contraseña, utilizando la base de datos.
    En caso de que se intente loguear sobre una cuenta ya logueada se devolvera un error por TCP.
    En caso de que la cuenta no exista se devolvera un error por TCP.
    Ademas permitira crear una nueva cuenta, sobre la cual realizara chequeos de validez de id de usuario.
    */
    std::pair<std::string, std::string> login(OrganizadorClientes &organizador);

    public:
    Cliente(Socket &&socket,
            OrganizadorSalas &organizadorSalas,
            OrganizadorClientes &organizadorClientes,
            BaseDeDatos &unaBaseDeDatos);
    Cliente(Cliente &&otro) = delete;
    Cliente(Cliente &otro) = delete;
    Cliente& operator=(Cliente &&otro) = delete;
    Cliente& operator=(Cliente &otro) = delete;
    /*
    Crea un nuevo Personaje utilizando la informacion de las credenciales, raza y clase pasadas por parametro.
    Lo inicializara en la posicion de inicio del mapa default y lo agregara a la base de datos.
    */
    void nuevoUsuario(std::pair<std::string, std::string> &credenciales, 
                      std::string &idRaza, 
                      std::string &idClase);
    std::string obtenerId();
    std::string& obtenerIdSala();
    Sala *obtenerSala();
    Personaje* obtenerPersonaje();
    /*
    Elimina al personaje de la sala en la cual se encuentra, eliminandolo asi del mapa.
    Carga al personaje en la nueva sala, segun el id pasado por parametro.
    La posicion del personaje sera cambiada a la de spawn del mapa destino.
    */
    void cambiarDeMapa(std::string &idMapa);
    /*
    Permite realizar el cambio de mapa que se describio en el metodo anterior con la posibilidad de 
    especificar la posicion destino.
    */
    void cambiarDeMapa(std::string &idMapa, Posicion nuevaPos);
    /*
    Comienza el procesamiento del cliente, en el cual se recibiran las operaciones, se las traduciran y
    encolaran en la cola de operaciones de la sala a la cual se pertenece.
    */
    void procesar();
    /*
    Indica si el cliente ha finalizado de procesar para poder ser liberado
    */
    bool haFinalizado();

    //Envio
    /*
    Envia informacion del contenido del mapa al cliente por medio de TCP.
    */
    void cargarMapa(const std::vector<char> &&infoMapa);
    /*
    Envia la siguiente informacion por medio de TCP:
    - Posiciones de cada una de las entidades del mapa en el cual se encuentra el personaje.
    - Caracterisitcas de dibujado de cada una de las entidades del mapa en el cual se encuentra el personaje.
    - Cada cierto tiempo se enviara ademas una actualizacion del inventario del personaje.
    */
    void actualizarEstado(const std::vector<struct PosicionEncapsulada> &posiciones,
                          const std::vector<SerializacionDibujado> &dibujado,
                          double tiempo);
    /*
    Envia un mensaje al cliente en formato cadena, 
    permitiendo indicar si el mismo sera publico por medio de TCP.
    */
    void enviarMensaje(const std::string& mensaje, bool mensaje_publico);
    /*
    Envia el contenido serializado de la tienda por medio de TCP.
    */
    void enviarTienda(const SerializacionContenedor &&serContenedor);
    /*
    Envia el contenido serializado del contenedor por medio de TCP.
    */
    void enviarContenedor(const SerializacionContenedor &&serContenedor);
    /*
    Envia el contenido del inventario del personaje por medio de TCP.
    */
    void enviarInventario();

    //ClienteProxy es friend de Cliente
    friend class ClienteProxy;
};

#endif
