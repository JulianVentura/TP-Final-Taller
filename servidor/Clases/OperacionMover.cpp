#include "OperacionMover.h"


OperacionMover::OperacionMover(Personaje *unPersonaje, 
                               DireccionMovimiento unaDireccion) : 
                               personaje(unPersonaje),
                               direccion(unaDireccion){}

OperacionMover::~OperacionMover(){
    //Do nothing
}

void OperacionMover::ejecutar(){
    switch (direccion){
        case MOVER_ARRIBA:
            personaje->moverHaciaArriba();
            break;
        case MOVER_ABAJO:
            personaje->moverHaciaAbajo();
            break;
        case MOVER_DERECHA:
            personaje->moverHaciaDerecha();
            break;
        case MOVER_IZQUIERDA:
            personaje->moverHaciaIzquierda();
            break;
        default:
            return;
    }
}