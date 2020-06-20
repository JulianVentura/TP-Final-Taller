#include "Personaje.h"
#include <utility>
#define VIDA_MAXIMA 50
#define MANA_MAXIMO 100
#define DESPLAZAMIENTO 8

Personaje::Personaje(float x, float y, std::string id) : 
                                       Entidad(VIDA_MAXIMA,
                                               MANA_MAXIMO,
                                               id){
    actualizarPosicion(std::move(Posicion(x, y)));
}
/*
Mas adelante la idea es que las funciones mover* cambien el estado
del personaje a "moviendose a tal lado".
Luego una llamada a personaje.actualizar() hara que la posicion se modifique
segun el estado.
Lo de abajo es solo para testeo
*/
Posicion Personaje::moverHaciaArriba(){
    Posicion temp(posicion);
    temp.PosicionAvanzarHaciaArriba(DESPLAZAMIENTO);
    return temp;
}
Posicion Personaje::moverHaciaAbajo(){
    Posicion temp(posicion);
    temp.PosicionAvanzarHaciaAbajo(DESPLAZAMIENTO);
    return temp;
}
Posicion Personaje::moverHaciaIzquierda(){
    Posicion temp(posicion);
    temp.PosicionAvanzarHaciaIzquierda(DESPLAZAMIENTO);
    return temp;
}
Posicion Personaje::moverHaciaDerecha(){
    Posicion temp(posicion);
    temp.PosicionAvanzarHaciaDerecha(DESPLAZAMIENTO);
    return temp;
}

Personaje::~Personaje(){}
