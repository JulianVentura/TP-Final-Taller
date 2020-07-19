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
    void cargarCliente(Cliente *cliente);
    void actualizarClientes(double tiempo);
    void eliminarCliente(const std::string &id);
    void persistirClientes(double tiempo);
    Mapa *obtenerMapa();
    std::string& obtenerNombre();
    void comenzar();
    void finalizar();
    ColaOperaciones* obtenerCola();
};


#endif
