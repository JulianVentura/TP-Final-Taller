#include "Pocion.h"
#include "Personaje.h"

Pocion::Pocion(unsigned int curVida, unsigned int curMana, std::string unId) : 
                                                           Item(unId),
                                                           curacionVida(curVida), 
                                                           curacionMana(curMana){}

void Pocion::utilizar(Personaje *personaje, unsigned int pos){
    personaje->curar(curacionVida, curacionMana);
    //personaje->eliminarDeInventario(pos);
}