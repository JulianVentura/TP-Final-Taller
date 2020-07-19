#include "OperacionAtacar.h"
#include "Cliente.h"
#include "Estado.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Entidad.h"

OperacionAtacar::OperacionAtacar(Cliente *unCliente, 
                                 Mapa *unMapa,
                                 std::string id) : 
                                 cliente(unCliente),
                                 mapa(unMapa),
                                 idObjetivo(id){}

OperacionAtacar::~OperacionAtacar(){}

void OperacionAtacar::ejecutar(){
    Entidad *entidad = mapa->obtener(idObjetivo);
    Personaje *personaje = cliente->obtenerPersonaje();
    entidad->serAtacadoPor(personaje);
}  