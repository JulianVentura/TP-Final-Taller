#ifndef __SALA_H__
#define __SALA_H__
#include "Cliente.h"
#include "Mapa.h"
#include "Excepcion.h"
#include "ColaSegura.h"
#include "GameLoop.h"
#include <map>
#include <mutex>


class Sala{
    private:
    std::string nombre;
    std::mutex mutex;
    std::map<std::string, Cliente*> clientes;
    Mapa mapa;
    ColaSegura colaOperaciones;
    GameLoop gameLoop;

    public:
    Sala(const char* nombreMapa);
    Sala(Sala &&otro) = delete;
    Sala(Sala &otro) = delete;
    Sala& operator=(Sala &otro) = delete;
    Sala& operator=(Sala &&otro) = delete;
    void cargarCliente(Cliente *cliente);
    void actualizarClientes(std::string &posiciones);
    void eliminarCliente(const char *id);
    std::string obtenerNombre();

};


#endif
