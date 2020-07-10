#include "Estado.h"
#include "Personaje.h"
#include "Entidad.h"

Estado::Estado(Personaje *unPersonaje) : personaje(unPersonaje){}

const uint16_t Estado::obtenerIDTCP() const {
    return idTCP;
}

Estado::~Estado(){}