#include "Proyectil.h"
#include "Configuraciones.h"
#include "Mapa.h"
#include <sstream>

#define LIMITE_CONTADOR 1000 

std::atomic<int> Proyectil::contador(0);

Proyectil::Proyectil(std::string unId, Posicion origen, Posicion unDestino) : Entidad(unId), 
                                                                              destino(unDestino),
                                                                              finalizado(false),
                                                                              haLlegadoADestino(false),
                                                                              tiempoTranscurrido(0),
                                                                              tiempoDespawn(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();                                                                          
    this->posicion = std::move(origen);
    this->desplazamiento = config->obtenerProyectilVelDesplazamiento(this->id);
    this->tiempoDespawn = config->obtenerProyectilTiempoDespawn(this->id);
    std::stringstream _id;
    if (contador >= LIMITE_CONTADOR) contador = 0;
    _id << id << "#" << contador;
    contador++;
    id = std::move(_id.str());
}

//Comercio

void Proyectil::interactuar(Estado *estado, Cliente *cliente){}

void Proyectil::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){}

void Proyectil::comprar(unsigned int pos, Estado *estado, Cliente *cliente){}

void Proyectil::vender(unsigned int pos, Estado *estado, Cliente *cliente){}

void Proyectil::vender(Item* item, Personaje *personaje, Cliente *cliente){}

void Proyectil::listar(Personaje *personaje, Cliente *cliente){}

void Proyectil::curar(Personaje *personaje, Cliente *cliente){}


//Ataque

std::string Proyectil::atacar(Personaje *objetivo){ return ""; }

std::string Proyectil::atacar(Criatura *objetivo){ return ""; }

void Proyectil::serAtacadoPor(Personaje *atacante){}

void Proyectil::serAtacadoPor(Criatura *atacante){}

std::string Proyectil::recibirDanio(int danio, Entidad *atacante){ return ""; }

void Proyectil::recibirCuracion(unsigned int curacion, Entidad *lanzador){}

//Estado

void Proyectil::actualizarEstado(double tiempo){
    if (haLlegadoADestino){
        tiempoTranscurrido += tiempo;
        if (tiempoTranscurrido >= tiempoDespawn) finalizado = true;
    }else{
        Posicion nuevaPos = std::move(this->posicion.perseguir(destino, desplazamiento, tiempo));
        if (posicion == nuevaPos) haLlegadoADestino = true;
        posicion.actualizarPosicion(std::move(nuevaPos));
    }
}

bool Proyectil::haFinalizado(){
    if (finalizado){
        mapaAlQuePertenece->eliminarEntidadNoColisionable(this);
    }
    return finalizado;
}

void Proyectil::dropearItems(Entidad *atacante){}

Proyectil::~Proyectil(){}