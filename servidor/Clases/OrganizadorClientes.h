#ifndef __ORGANIZADOR_CLIENTES_H__
#define __ORGANIZADOR_CLIENTES_H__
#include <map>
#include <memory>
#include <mutex>
#include "Cliente.h"
class OrganizadorClientes{
    private:
    std::list<std::unique_ptr<Cliente>> noInicializados;
    std::map<std::string, std::unique_ptr<Cliente>> clientes;
    std::mutex mutex;

    bool _idEnUso(std::string &id);
    public:
    OrganizadorClientes();
    OrganizadorClientes(OrganizadorClientes &otro) = delete;
    OrganizadorClientes(OrganizadorClientes &&otro) = delete;
    OrganizadorClientes& operator=(OrganizadorClientes &otro) = delete;
    OrganizadorClientes& operator=(OrganizadorClientes &&otro) = delete;
    /*
    Incorpora un cliente a la lista de clientes no inicializados.
    */
    void incorporarCliente(std::unique_ptr<Cliente> unCliente);
    /*
    Inicializa un cliente de la lista de no inicializados.
    En caso de que el cliente no se encuentre en la lista lanza Excepcion.
    */
    void inicializarCliente(Cliente *cliente);
    /*
    Obtiene un puntero a Cliente dada su id. El cliente debera pertenecer a los inicializados.
    */
    Cliente* obtenerCliente(std::string id);
    void recuperarFinalizados();
    void recuperarTodosLosClientes();
    bool idEnUso(std::string &id);
    /*
    Aplica la funcion pasada por parametro a cada uno de los clientes inicializados.
    */
    void aplicarFuncion(std::function<void(std::unique_ptr<Cliente>&, void*)> funcion, void* dato);
};

#endif
