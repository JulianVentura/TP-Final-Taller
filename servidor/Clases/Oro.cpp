#include "Oro.h"
#include "Personaje.h"

Oro::Oro(unsigned int cantOro) : cantidadOro(cantOro){}

void Oro::utilizar(Personaje *personaje, unsigned int pos){
    personaje->recibirOro(cantidadOro);
    personaje->eliminarDeInventario(pos);
}