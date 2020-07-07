#include "Armadura.h"
#include "Personaje.h"

Armadura::Armadura(unsigned int defMax, 
                   unsigned int defMin, 
                   std::string unId,
                   unsigned int unPrecio) : 
                   Item(unId, unPrecio), 
                   PiezaDeDefensa(defMax, defMin){}


void Armadura::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}