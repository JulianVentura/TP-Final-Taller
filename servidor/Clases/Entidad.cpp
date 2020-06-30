#include "Entidad.h"
#include "Mapa.h"

Entidad::Entidad(unsigned int vida, 
                 unsigned int mana,
                 float x,
                 float y, 
                 std::string &unId) : 
                 Posicionable(x, y),
                 vidaMaxima(vida),
                 manaMaximo(mana),
                 vidaActual(0),
                 manaActual(0),
                 id(unId){}


const quadtree::Box<float>& Entidad::obtenerArea() const{
    return posicion.obtenerAreaQueOcupa();
}

bool Entidad::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Entidad::colisionaCon(const quadtree::Box<float> &area) const{
    return posicion.obtenerAreaQueOcupa().intersects(area);
}
std::string Entidad::obtenerId(){
    return std::move(id);
}

void Entidad::actualizarEstado(double tiempo, Mapa *mapa){
    /* Actualizar estado */
    /*
    1- Regenerar vida
    2- Regenerar mana
    3- Moverse
    */
    Posicion nuevaPosicion = posicion.mover();
    mapa->actualizarPosicion(this, std::move(nuevaPosicion));
}

Entidad::~Entidad(){}


