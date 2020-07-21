#ifndef __SALA_H__
#define __SALA_H__
#include "Mapa.h"
#include "../../common/Excepcion.h"
#include "ColaOperaciones.h"
#include "BuclePrincipal.h"
#include "ColaDeSerializacion.h"
#include <map>
#include <mutex>

class Cliente;
class Sala{
    private:
    std::string nombre;
    std::mutex mutex;
    std::map<std::string, Cliente*> clientes;
    Mapa mapa;
    ColaOperaciones colaOperaciones;
    BuclePrincipal buclePrincipal;
    ColaSerializacion &colaSerializacion;
    double tiempoTranscurrido;
    double tiempoPersistencia;

    public:
    Sala(std::string nombreMapa, ColaSerializacion &cola);
    Sala(Sala &&otro) = delete;
    Sala(Sala &otro) = delete;
    Sala& operator=(Sala &otro) = delete;
    Sala& operator=(Sala &&otro) = delete;
    /*
    Carga un nuevo cliente a la sala y a su personaje al mapa
    */
    void cargarCliente(Cliente *cliente);
    /*
    Envia informacion de las posiciones de las entidades, dibujado de los personajes a los
    clientes conectados
    */
    void actualizarClientes(double tiempo);
    /*
    Elimina el cliente de id de la sala y a su personaje del mapa
    */
    void eliminarCliente(const std::string &id);
    /*
    Persiste todos los clientes conectados a la sala, sin bloquearse.
    */
    void persistirClientes(double tiempo);
    Mapa *obtenerMapa();
    std::string& obtenerNombre();
    void comenzar();
    void finalizar();
    ColaOperaciones* obtenerCola();
};


#endif
