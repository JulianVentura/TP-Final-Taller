#ifndef __ORGANIZADOR_CLIENTES_H__
#define __ORGANIZADOR_CLIENTES_H__
#include <map>
#include <memory>
#include <mutex>
#include "Cliente.h"
class OrganizadorClientes{
    private:
    std::map<std::string, std::unique_ptr<Cliente>> clientes;
    std::mutex mutex;
    public:
    OrganizadorClientes();
    OrganizadorClientes(OrganizadorClientes &otro) = delete;
    OrganizadorClientes(OrganizadorClientes &&otro) = delete;
    OrganizadorClientes& operator=(OrganizadorClientes &otro) = delete;
    OrganizadorClientes& operator=(OrganizadorClientes &&otro) = delete;
    void incorporarCliente(std::unique_ptr<Cliente> unCliente);
    Cliente* obtenerCliente(std::string id);
    void recuperarFinalizados();
    void recuperarTodosLosClientes();
    bool idEnUso(std::string &id);
    void aplicarFuncion(std::function<void(std::unique_ptr<Cliente>&, void*)> funcion, void* dato);
};

#endif
