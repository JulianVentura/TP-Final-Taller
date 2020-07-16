#include "Item.h"

Item::Item(std::string unId, uint16_t unidTCP, unsigned int unPrecio) : 
                                               id(unId),
                                               idTCP(unidTCP), 
                                               precio(unPrecio){
    //Do nothing
}

Item::~Item(){
    //Do nothing
}

std::string Item::obtenerId(){
    return id;
}

unsigned int Item::obtenerPrecio(){
    return precio;
}

const uint16_t Item::obtenerIDTCP() const{
    return idTCP;
}

const SerializacionItem Item::serializar() const{
    SerializacionItem ser = {0, 0};
    ser.idTCP  = this->idTCP;
    ser.precio = this->precio;
    return ser;
}