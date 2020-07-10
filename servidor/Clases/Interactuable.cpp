#include "Interactuable.h"
#define DIST_INTERACCION 50





Interactuable::Interactuable(std::string unId) : 
                                      id(unId),
                                      distanciaMaximaDeInteraccion(DIST_INTERACCION){
    //La distancia maxima de interaccion deberia ser levantada del json.
}

const std::string Interactuable::obtenerId() const{
    return id;
}

Interactuable::~Interactuable(){}