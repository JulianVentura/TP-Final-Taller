#include "Criatura.h"
#include <utility>
#define VIDA_MAXIMA 50 //cambiar
#define MANA_MAXIMO 100 //cambiar
#define DESPLAZAMIENTO 20 //cambiar

Criatura::Criatura(float x, float y, const char* id) : 
                                       Entidad(VIDA_MAXIMA,
                                               MANA_MAXIMO,
                                               id){
    actualizarPosicion(std::move(Posicion(x, y)));
}

Criatura::~Criatura(){}