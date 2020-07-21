#include "Entidad.h"
#include "Mapa.h"
#include "../../common/Excepcion.h"
#include <vector>
#include <cstring>

Entidad::Entidad(std::string unId) : 
                 Interactuable(unId),
                 vidaMaxima(0),
                 vidaActual(0),
                 manaMaximo(0),
                 manaActual(0),
                 fuerza(0),
                 inteligencia(0),
                 agilidad(0),
                 constitucion(0),
                 nivel(0),
                 mapaAlQuePertenece(nullptr){}


void Entidad::consumirMana(unsigned int cantidad){
    if ((manaActual - cantidad) < 0){
        throw Excepcion("Error Entidad: No hay mana suficiente para consumir");
    }
    manaActual -= cantidad;
}

bool Entidad::manaSuficiente(unsigned int cantidad){
    if ((manaActual - cantidad) < 0) return false;
    return true;
}

void Entidad::indicarMapaAlQuePertenece(Mapa *mapa){
    this->mapaAlQuePertenece = mapa;
}

void Entidad::obtenerExperiencia(unsigned int cantidad){
    //Nada
}

void Entidad::recibirOro(unsigned int cantidad){
    //Nada
}


bool Entidad::haFinalizado(){
    return false;
}

//Serializacion
const struct PosicionEncapsulada Entidad::serializarPosicion() const{
    struct PosicionEncapsulada pos = std::move(posicion.serializarPosicion());
    const char *buff = this->obtenerId().c_str();
    strncpy(pos.id, buff, TAM_ID);
    pos.id[TAM_ID - 1] = 0;
    return pos;
}

Entidad::~Entidad(){}