#include "OperacionTransaccion.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"

OperacionTransaccion::OperacionTransaccion(Cliente *unCliente, 
                                           Mapa *unMapa,
                                           std::string id,
                                           bool deposito) : 
                                           cliente(unCliente),
                                           mapa(unMapa),
                                           idObjetivo(id),
                                           esDeposito(deposito){}

OperacionTransaccion::~OperacionTransaccion(){}

void OperacionTransaccion::ejecutar(){
    Entidad *entidad = mapa->obtener(idObjetivo);
    Personaje *personaje = cliente->obtenerPersonaje();
    Estado *estado = personaje->obtenerEstado();
    entidad->transaccion(esDeposito, estado, cliente);
} 