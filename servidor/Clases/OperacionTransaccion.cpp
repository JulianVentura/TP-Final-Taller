#include "OperacionTransaccion.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Interactuable.h"
#include <iostream> //DEBUG

OperacionTransaccion::OperacionTransaccion(Cliente *unCliente, 
                                           Mapa *unMapa,
                                           std::string id,
                                           bool deposito) : 
                                           cliente(unCliente),
                                           mapa(unMapa),
                                           idObjetivo(id),
                                           esDeposito(deposito){}

OperacionTransaccion::~OperacionTransaccion(){
    //Do nothing
}

void OperacionTransaccion::ejecutar(){
    try{
        Entidad *entidad = mapa->obtener(idObjetivo);
        Personaje *personaje = cliente->obtenerPersonaje();
        Estado *estado = personaje->obtenerEstado();
        entidad->transaccion(esDeposito, estado, cliente);
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido atrapado en OperacionVender" << std::endl;
    }
} 