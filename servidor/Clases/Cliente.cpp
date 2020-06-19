#include "Cliente.h"

Cliente::Cliente(std::string &unId) : personaje(0, 0, unId),
                                      id(unId){}

void Cliente::enviarPosiciones(std::string &posiciones){

}
std::string Cliente::obtenerId(){
    return this->id;
}
Personaje* Cliente::obtenerPersonaje(){
    return &personaje;
}