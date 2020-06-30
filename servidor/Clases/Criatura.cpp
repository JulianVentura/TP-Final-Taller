#include "Criatura.h"
#include <utility>
#define VIDA_MAXIMA 50 //cambiar
#define MANA_MAXIMO 100 //cambiar
#define DESPLAZAMIENTO 2 //cambiar
#define NIVEL_MINIMO 1 //Cambiar

Criatura::Criatura(float x, float y, std::string unId) : 
                                       Entidad(VIDA_MAXIMA,
                                               MANA_MAXIMO,
                                               0,
                                               NIVEL_MINIMO,   
                                               x,
                                               y,
                                               unId){
    desplazamiento = DESPLAZAMIENTO;
}

Criatura::~Criatura(){}