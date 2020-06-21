#include "OperacionDetenerse.h"


OperacionDetenerse::OperacionDetenerse(Personaje *unPersonaje) : 
                                       personaje(unPersonaje){}

OperacionDetenerse::~OperacionDetenerse(){
    //Do nothing
}

void OperacionDetenerse::ejecutar(){
    personaje->detenerse();
}