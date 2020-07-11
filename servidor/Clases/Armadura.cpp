#include "Armadura.h"
#include "Personaje.h"

Armadura::Armadura(unsigned int defMax, 
                   unsigned int defMin, 
                   std::string unId,
                   uint16_t idTCP,
                   unsigned int unPrecio) : 
                   Item(unId, idTCP, unPrecio), 
                   PiezaDeDefensa(defMax, defMin){}


void Armadura::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}

void Armadura::desequipar(Personaje *personaje){
    personaje->equipar(this);
}
