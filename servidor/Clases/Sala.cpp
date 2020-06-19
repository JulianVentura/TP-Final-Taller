#include "Sala.h"

Sala::Sala(const char* nombreMapa) : mapa(std::string(nombreMapa) + ".json"),
                                     colaOperaciones(),
                                     gameLoop(colaOperaciones, mapa, *this)
                                     {}

void Sala::cargarCliente(Cliente *cliente){
    if (clientes.count(cliente->obtenerId())){
        throw Excepcion("El cliente ya esta cargado en el mapa");
    }
    clientes[cliente->obtenerId()] = cliente;
}
void Sala::actualizarClientes(std::string &posiciones){
    for (auto& cliente : clientes){
        cliente.second->enviarPosiciones(posiciones);
    }
}
void Sala::eliminarCliente(const char *id){

}
std::string Sala::obtenerNombre(){
    return this->nombre;
}