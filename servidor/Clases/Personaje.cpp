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

Personaje::~Personaje(){}
