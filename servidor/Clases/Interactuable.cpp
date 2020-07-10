#include "Interactuable.h"
#include "Configuraciones.h"




Interactuable::Interactuable(std::string unId) : 
                                      id(unId),
                                      distanciaMaximaDeInteraccion(0){
    //La distancia maxima de interaccion deberia ser levantada del json.
    Configuraciones *config = Configuraciones::obtenerInstancia();
    distanciaMaximaDeInteraccion = config->obtenerDistanciaMaximaDeInteraccion();
}

const std::string Interactuable::obtenerId() const{
    return id;
}

Interactuable::~Interactuable(){}