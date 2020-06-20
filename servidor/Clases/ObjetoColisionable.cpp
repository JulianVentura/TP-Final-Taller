#include "ObjetoColisionable.h"
#include <utility>

ObjetoColisionable::ObjetoColisionable(quadtree::Box<float> &&rectangulo) : 
                                       areaQueOcupa(std::move(rectangulo)){}

ObjetoColisionable::ObjetoColisionable(ObjetoColisionable &&otro) : 
                    ObjetoColisionable(std::move(otro.areaQueOcupa)){}

const quadtree::Box<float>& ObjetoColisionable::obtenerArea() const{
    return this->areaQueOcupa;
}

bool ObjetoColisionable::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(this->areaQueOcupa);
}

bool ObjetoColisionable::colisionaCon(const quadtree::Box<float> &otroArea) const{
    return this->areaQueOcupa.intersects(otroArea);
}

ObjetoColisionable::~ObjetoColisionable(){
    //Do nothing
}

