#include "OrganizadorClientes.h"
#include "../../common/Excepcion.h"

OrganizadorClientes::OrganizadorClientes(){
    //Do nothing
}

void OrganizadorClientes::incorporarCliente(std::unique_ptr<Cliente> unCliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    noInicializados.push_back(std::move(unCliente));
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
    std::list<std::unique_ptr<Cliente>>::iterator itN = noInicializados.begin();
    while (itN != noInicializados.end()){
        if (itN->get()->haFinalizado()){
            itN->get()->recuperar();
            itN = noInicializados.erase(itN);
        }else{
            ++itN;
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
    std::list<std::unique_ptr<Cliente>>::iterator itN = noInicializados.begin();
    while (itN != noInicializados.end()){
        itN->get()->recuperar();
        ++itN;
    }
}

bool OrganizadorClientes::idEnUso(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    return _idEnUso(id);
}

void OrganizadorClientes::aplicarFuncion
    (std::function<void(std::unique_ptr<Cliente>&, void*)> funcion, void* dato){
    for (auto& par : clientes){
        funcion(par.second, dato);
     }
 }


 void OrganizadorClientes::inicializarCliente(Cliente *cliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string id = cliente->obtenerId();
    std::list<std::unique_ptr<Cliente>>::iterator it = noInicializados.begin();
     while (it != noInicializados.end()){
        if (it->get() == cliente) break;
        ++it;
    }
    if (it == noInicializados.end()){
        throw Excepcion
        ("Error en OrganizadorClientes: "
        "Se ha intentado inicializar un cliente de id %s, pero este no se encuentra almacenado", id.c_str());
    }
    if (_idEnUso(id)){
        throw Excepcion
        ("Error en OrganizadorClientes: "
        "Se ha intentado inicializar un cliente de id %s, pero esta id ya se encuentra en uso", id.c_str());
    }
    clientes[id] = std::move((*it));
    noInicializados.erase(it);
 }

bool OrganizadorClientes::_idEnUso(std::string &id){
    std::map<std::string, std::unique_ptr<Cliente>>::iterator it = clientes.find(id);
    if (it == clientes.end()) return false;
    return true;
}