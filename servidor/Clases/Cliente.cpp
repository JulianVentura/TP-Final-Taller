#include "Cliente.h"
#include <iostream> //DEBUG

Cliente::Cliente(std::string unId, 
                 std::string nombreMapa, 
                 Sala &sala) : 
                 personaje(0, 0, unId),
                 id(unId){
    sala.cargarCliente(this);
}

void Cliente::enviarPosiciones(std::vector<struct PosicionEncapsulada> &posiciones){
    //Enviar las posiciones a traves de ClienteProxy
}   
std::string Cliente::obtenerId(){
    return this->id;
}
Personaje* Cliente::obtenerPersonaje(){
    return &personaje;
}