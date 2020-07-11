#include "Casco.h"
#include "Personaje.h"

Casco::Casco(unsigned int defMax, 
             unsigned int defMin, 
             std::string unId,
             uint16_t idTCP,
             unsigned int unPrecio) : 
             Item(unId, idTCP, unPrecio), 
             PiezaDeDefensa(defMax, defMin){}


void Casco::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}

void Casco::desequipar(Personaje *personaje){
    personaje->equipar(this);
}
