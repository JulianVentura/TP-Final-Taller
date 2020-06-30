#include "Servidor.h"
#include <iostream>
#define TECLA_ESCAPE "q"
#define HOST_DEFAULT "localhost"
#include "Configuraciones.h"
Servidor::Servidor(const char* puerto) : organizadorSalas(),
                                         baseDeDatos(),
                                         aceptador(HOST_DEFAULT, puerto, organizadorSalas, baseDeDatos){
    Configuraciones::crearInstancia("NombreADefinir");
}

void Servidor::procesar(){
    organizadorSalas.comenzar();
    aceptador.comenzar();
    std::string entrada("");
    while (entrada != TECLA_ESCAPE){
        std::cin >> entrada;
    }
    aceptador.finalizar();
    aceptador.recuperar();
    organizadorSalas.finalizar();
}