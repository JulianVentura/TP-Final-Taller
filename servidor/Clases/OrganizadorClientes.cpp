#include "OrganizadorClientes.h"
#include "Excepcion.h"


OrganizadorClientes::OrganizadorClientes(){
    //Do nothing
}

void OrganizadorClientes::incorporarCliente(std::unique_ptr<Cliente> unCliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string id = unCliente.get()->obtenerId();
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.find(id);
    if (it != clientes.end()){
        throw Excepcion
        ("Error en OrganizadorClientes: "
        "Se ha intentado ingresar un cliente ya existente, de id %s", id.c_str());
    }
    clientes[id] = std::move(unCliente);
}
Cliente* OrganizadorClientes::obtenerCliente(std::string id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.find(id);
    if (it == clientes.end()){
        throw Excepcion
        ("Error en OrganizadorClientes: "
        "Se ha intentado obtener un cliente de id %s, pero este no se encuentra almacenado", id.c_str());
    }
    return it->second.get();
}
void OrganizadorClientes::recuperarFinalizados(){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.begin();
    while (it != clientes.end()){
        if (it->second.get()->haFinalizado()){
            it->second.get()->recuperar();
            it = clientes.erase(it);
        }else{
            ++it;
        }
    }
}
void OrganizadorClientes::recuperarTodosLosClientes(){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.begin();
    while (it != clientes.end()){
           it->second.get()->recuperar();
           ++it;
    }
}

bool OrganizadorClientes::idEnUso(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.find(id);
    if (it == clientes.end()) return false;
    return true;
}

void OrganizadorClientes::aplicarFuncion
    (std::function<void(std::unique_ptr<Cliente>&, void*)> funcion, void* dato){
    for (auto& par : clientes){
        funcion(par.second, dato);
     }
 }