#include "Escudo.h"
#include "Personaje.h"

Escudo::Escudo(unsigned int defMax, unsigned int defMin, std::string unId) : 
Item(unId), PiezaDeDefensa(defMax, defMin){}


void Escudo::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}