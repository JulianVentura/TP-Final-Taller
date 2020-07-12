#include "Pocion.h"
#include "Personaje.h"

Pocion::Pocion(unsigned int curVida, 
               unsigned int curMana, 
               std::string unId,
               uint16_t idTCP,
               unsigned int unPrecio) : 
               Item(unId, idTCP, unPrecio),
               curacionVida(curVida), 
               curacionMana(curMana){}

void Pocion::utilizar(Personaje *personaje, unsigned int pos){
    personaje->curar(curacionVida, curacionMana);
    personaje->eliminarDeInventario(pos);
}

void Pocion::desequipar(Personaje *personaje, unsigned int pos){
    //Una pocion no se puede desequipar
}