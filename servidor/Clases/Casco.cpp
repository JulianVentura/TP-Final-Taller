#include "Casco.h"
#include "Personaje.h"

Casco::Casco(unsigned int defMax, 
             unsigned int defMin, 
             std::string unId,
             unsigned int unPrecio) : 
             Item(unId, unPrecio), 
             PiezaDeDefensa(defMax, defMin){}


void Casco::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}