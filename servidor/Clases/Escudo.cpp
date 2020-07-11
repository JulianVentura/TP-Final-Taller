#include "Escudo.h"
#include "Personaje.h"

Escudo::Escudo(unsigned int defMax, 
               unsigned int defMin, 
               std::string unId,
               uint16_t idTCP,
               unsigned int unPrecio) : 
               Item(unId, idTCP, unPrecio), 
               PiezaDeDefensa(defMax, defMin){}


void Escudo::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this, pos);
}

void Escudo::desequipar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this, pos);
}