#include "ObjetoColisionable.h"
#include <utility>

ObjetoColisionable::ObjetoColisionable(Rectangulo &&rectangulo) : 
                                       areaQueOcupa(std::move(rectangulo)){}

ObjetoColisionable::ObjetoColisionable(ObjetoColisionable &&otro) : 
                    ObjetoColisionable(std::move(otro.areaQueOcupa)){}

Rectangulo& ObjetoColisionable::obtenerArea(){
    return this->areaQueOcupa;
}

bool ObjetoColisionable::colisionaCon(Colisionable &otro){
    return otro.colisionaCon(this->areaQueOcupa);
}

bool ObjetoColisionable::colisionaCon(Rectangulo &otroArea){
    return this->areaQueOcupa.seSuperponeCon(otroArea);
}

ObjetoColisionable::~ObjetoColisionable(){
    //Do nothing
}

