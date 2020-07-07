#include "Estado.h"
#include "Personaje.h"
#include "Entidad.h"

Estado::Estado(Personaje *unPersonaje) : personaje(unPersonaje){}

void Estado::interactuarCon(Entidad *entidad){
    //Do nothing
}

const uint16_t Estado::obtenerIDTCP() const {
    return idTCP;
}

Estado::~Estado(){}