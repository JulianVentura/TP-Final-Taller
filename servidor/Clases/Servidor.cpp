#include "Servidor.h"
#include <iostream>
#define TECLA_ESCAPE "q"

Servidor::Servidor(const char* host) : organizadorSalas(),
                                       baseDeDatos(),
                                       aceptador(host, organizadorSalas, baseDeDatos){}


void Servidor::procesar(){
    aceptador.comenzar();
    std::string entrada("");
    while (entrada != TECLA_ESCAPE){
        std::cin >> entrada;
    }
    aceptador.finalizar();
    aceptador.recuperar();
}