#include "OperacionAtacar.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Entidad.h"
#include <iostream> //DEBUG

OperacionAtacar::OperacionAtacar(Cliente *unCliente, 
                                 Mapa *unMapa,
                                 Divulgador *unDivulgador,
                                 std::string id) : 
                                 cliente(unCliente),
                                 divulgador(unDivulgador),
                                 mapa(unMapa),
                                 idObjetivo(id){}

OperacionAtacar::~OperacionAtacar(){
    //Do nothing
}

void OperacionAtacar::ejecutar(){
    try{
        Entidad *entidad = mapa->obtener(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        entidad->serAtacadoPor(personaje, divulgador);
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
}  