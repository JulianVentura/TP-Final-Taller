#include "Servidor.h"
#include "Configuraciones.h"
#include <iostream>
#define TECLA_ESCAPE "q"

Servidor::Servidor(const char* archivoConfig) : organizadorSalas(archivoConfig),
                                                baseDeDatos(),
                                                aceptador(organizadorSalas, 
                                                          baseDeDatos){
    //Configuraciones *config = FabricaDeItems::obtenerInstancia();
    //fabrica->obtenerItemIDTCP(4);
    //Si aca creo el singleton entonces no va a estar inicializado para cuando se llame a la member
}


//Se podria obtener la tecla de escape del archivo de config tambien.
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