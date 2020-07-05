#include "Estado.h"
#include "Personaje.h"
#include "Entidad.h"

Estado::Estado(Personaje *unPersonaje) : personaje(unPersonaje){}

void Estado::interactuarCon(Entidad *entidad){
    //Do nothing
}

Estado::~Estado(){}