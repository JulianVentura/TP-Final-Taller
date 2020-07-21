#include "Sala.h"
#include "Cliente.h"
#include "Configuraciones.h"
#include "../../common/Serializacion.h"

Sala::Sala(std::string nombreMapa, ColaSerializacion &cola) : 
                                     nombre(nombreMapa),
                                     mapa(nombreMapa),
                                     colaOperaciones(),
                                     buclePrincipal(colaOperaciones, mapa, *this),
                                     colaSerializacion(cola),
                                     tiempoTranscurrido(0),
                                     tiempoPersistencia(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    tiempoPersistencia = config->obtenerSalaTiempoPersistencia();
}


void Sala::cargarCliente(Cliente *cliente){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (clientes.count(cliente->obtenerId())){
        throw Excepcion("Error en Cliente: "
        "El cliente de id %s ya esta cargado en el mapa %s", cliente->obtenerId().c_str(), nombre.c_str());
    }
    clientes[cliente->obtenerId()] = cliente;
    mapa.cargarEntidad(cliente->obtenerPersonaje());
    cliente->cargarMapa(std::move(mapa.obtenerInformacionMapa()));
}
void Sala::actualizarClientes(double tiempo){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::vector<struct PosicionEncapsulada> posiciones = std::move(mapa.recolectarPosiciones());
    std::vector<SerializacionDibujado> dibujado;
    //Construyo el vector de dibujado de cada cliente.
    for (auto& cliente : clientes){
        dibujado.push_back(std::move(cliente.second->obtenerPersonaje()->serializarDibujado()));
    }
    for (auto& cliente : clientes){
        cliente.second->actualizarEstado(posiciones, dibujado, tiempo);
    }
}
void Sala::eliminarCliente(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::map<std::string, Cliente*>::iterator it = clientes.find(id);
    if (it == clientes.end()) return;
    clientes.erase(it);
    mapa.eliminarEntidad(id);
}

void Sala::persistirClientes(double tiempo){
    std::unique_lock<std::mutex> lock(this->mutex);
    tiempoTranscurrido += tiempo;
    if (tiempoTranscurrido < tiempoPersistencia) return;
    tiempoTranscurrido = 0;
    for (auto& cliente : clientes){
        colaSerializacion.push(std::move(cliente.second->serializar()));
    }
}

std::string& Sala::obtenerNombre(){
    //Aca no es necesario hacer un lock, el nombre no sera modificado.
    return this->nombre;
}

void Sala::comenzar(){
    buclePrincipal.comenzar();
}

void Sala::finalizar(){
    buclePrincipal.finalizar();
    buclePrincipal.recuperar();
}

Mapa* Sala::obtenerMapa(){
    return &this->mapa;
}

ColaOperaciones* Sala::obtenerCola(){
    return &colaOperaciones;
}
