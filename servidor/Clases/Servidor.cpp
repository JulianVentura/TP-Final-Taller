#include "Servidor.h"
#include "Configuraciones.h"
#include <iostream>
#define TECLA_ESCAPE "q"

Servidor::Servidor(const char* archivoConfig) : organizadorSalas(archivoConfig, colaSerializacion),
                                                baseDeDatos(),
                                                aceptador(organizadorSalas, 
                                                          baseDeDatos),
                                                persistidor(colaSerializacion, baseDeDatos){
    //Si aca creo el singleton entonces no va a estar inicializado para cuando se llame a la member
}


void Servidor::procesar(){
    organizadorSalas.comenzar();
    aceptador.comenzar();
    persistidor.comenzar();
    std::string entrada("");
    while (entrada != TECLA_ESCAPE){
        std::cin >> entrada;
    }
    aceptador.finalizar();
    aceptador.recuperar();
    organizadorSalas.finalizar();
    colaSerializacion.cerrarCola();
    persistidor.recuperar();
}