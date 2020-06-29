#ifndef __SALA_H__
#define __SALA_H__
#include "Mapa.h"
#include "Excepcion.h"
#include "ColaOperaciones.h"
#include "GameLoop.h"
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
    GameLoop gameLoop;

    public:
    Sala(const char* nombreMapa);
    Sala(Sala &&otro) = delete;
    Sala(Sala &otro) = delete;
    Sala& operator=(Sala &otro) = delete;
    Sala& operator=(Sala &&otro) = delete;
    void cargarCliente(Cliente *cliente);
    void actualizarClientes();
    void eliminarCliente(const std::string &id);
    std::string& obtenerNombre();
    void comenzar();
    void finalizar();
    ColaOperaciones* obtenerCola();
};


#endif
