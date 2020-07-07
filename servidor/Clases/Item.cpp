#include "Item.h"

Item::Item(std::string unId, unsigned int unPrecio) : id(unId), precio(unPrecio){
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