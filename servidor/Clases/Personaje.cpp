#include "Personaje.h"
#include <utility>
#define VIDA_MAXIMA 50
#define MANA_MAXIMO 100
#define DESPLAZAMIENTO 4

Personaje::Personaje(float x, float y, std::string id) : 
                                       Entidad(VIDA_MAXIMA,
                                               MANA_MAXIMO,
                                               x,
                                               y,
                                               id){
    desplazamiento = DESPLAZAMIENTO;
}
Personaje& Personaje::operator=(Personaje &&otro){
    this->vidaActual = otro.vidaActual;
    this->manaActual = otro.manaActual;
    this->vidaMaxima = otro.vidaMaxima;
    this->vidaActual = otro.vidaActual;
    this->id = std::move(otro.id);
    this->posicion = std::move(otro.posicion);
    this->desplazamiento = otro.desplazamiento;
    //No hay necesidad de modificar a "otro", no puede haber ningun problema.
    return *this;
}
Personaje::~Personaje(){}
