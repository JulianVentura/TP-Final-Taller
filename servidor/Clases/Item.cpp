#include "Item.h"

Item::Item(std::string unId) : id(unId){
    //Do nothing
}

Item::~Item(){
    //Do nothing
}

std::string Item::obtenerId(){
    return id;
}