#include "Sala.h"
#include "Cliente.h"
#include "PosicionEncapsulada.h"

Sala::Sala(std::string nombreMapa) : nombre(nombreMapa),
                                     mapa(nombreMapa),
                                     colaOperaciones(),
                                     gameLoop(colaOperaciones, mapa, *this){}


void Sala::cargarCliente(Cliente *cliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (clientes.count(cliente->obtenerId())){
        throw Excepcion("Error en Cliente: "
        "El cliente de id %s ya esta cargado en el mapa", cliente->obtenerId());
    }
    clientes[cliente->obtenerId()] = cliente;
    mapa.cargarPersonaje(cliente->obtenerPersonaje());
    cliente->cargarMapa(std::move(mapa.obtenerInformacionMapa()));
}
void Sala::actualizarClientes(){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::vector<struct PosicionEncapsulada> posiciones = std::move(mapa.recolectarPosiciones());
    for (auto& cliente : clientes){
        cliente.second->actualizarEstado(posiciones);
    }
}
void Sala::eliminarCliente(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, Cliente*>::iterator it = clientes.find(id);
    if (it == clientes.end()) return;
    clientes.erase(it);
    mapa.eliminarEntidad(id);
}
std::string& Sala::obtenerNombre(){
    //Aca no es necesario hacer un lock, el nombre no sera modificado.
    return this->nombre;
}

void Sala::comenzar(){
    gameLoop.comenzar();
}

void Sala::finalizar(){
    gameLoop.finalizar();
    gameLoop.recuperar();
}

ColaOperaciones* Sala::obtenerCola(){
    return &colaOperaciones;
}

/*
El GameLoop va a iterar constantemente y le pedira a la sala que le fowardee las posiciones a todos los clientes.
Cuando eso suceda el gameloop quedara bloqueado dentro de Sala::actualizarClientes() ya que el metodo sera atomico.
Si justo algun cliente intenta loguearse entonces el GameLoop se quedara bloqueado hasta que este cliente se haya cargado
correctamente tanto en el mapa como en la lista de clientes.
Si justo algun cliente intenta desloguearse sucedera lo mismo.
Por lo tanto la sala debera encargarse de solicitarle al mapa las posiciones de las entidades, no el GameLoop.

*/