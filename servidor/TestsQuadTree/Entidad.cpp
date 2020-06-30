#include "Entidad.h"


Entidad::Entidad(unsigned int vida, unsigned int mana, std::string &unId) : 
                                                            vidaMaxima(vida),
                                                            manaMaximo(mana),
                                                            id(unId){}


const quadtree::Box<float>& Entidad::obtenerArea() const{
    return posicion.obtenerAreaQueOcupa();
}

bool Entidad::colisionaCon(const Colisionable &otro) const{
    //quadtree::Box<float> area = std::move(posicion.obtenerAreaQueOcupa());
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Entidad::colisionaCon(const quadtree::Box<float> &area) const{
    return posicion.obtenerAreaQueOcupa().intersects(area);
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


