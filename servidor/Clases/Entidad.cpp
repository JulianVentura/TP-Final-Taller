#include "Entidad.h"


Entidad::Entidad(unsigned int vida, unsigned int mana, const char* id) : 
                                                            vidaMaxima(vida),
                                                            manaMaximo(mana),
                                                            id(id){}


Rectangulo& Entidad::obtenerArea(){
    return posicion.obtenerAreaQueOcupa();
}

bool Entidad::colisionaCon(Colisionable &otro){
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Entidad::colisionaCon(Rectangulo &area){
    return posicion.obtenerAreaQueOcupa().seSuperponeCon(area);
}
std::string Entidad::obtenerId(){
    return std::move(id);
}

Posicion&& Entidad::avanzar(){
    //Cambiar esto
    return std::move(posicion);
}

void Entidad::actualizarEstado(double tiempo){
    /* Actualizar estado */
}

Entidad::~Entidad(){}


