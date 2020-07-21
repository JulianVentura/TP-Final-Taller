#include "Interactuable.h"
#include "Configuraciones.h"




Interactuable::Interactuable(std::string unId) : 
                                      id(unId),
                                      distanciaMaximaDeInteraccion(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    distanciaMaximaDeInteraccion = config->obtenerDistanciaMaximaDeInteraccion();
}

const std::string Interactuable::obtenerId() const{
    return id;
}

Interactuable::~Interactuable(){}