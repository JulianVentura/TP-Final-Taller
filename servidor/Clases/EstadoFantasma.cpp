#include "EstadoFantasma.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Arma.h"
#include "Mapa.h"
#include "Configuraciones.h"

EstadoFantasma::EstadoFantasma(Personaje *unPersonaje) : Estado(unPersonaje){}

void EstadoFantasma::interactuar(Entidad *entidad){
    //Interactuar normalmente.
}

/*
void EstadoFantasma::interactuar(Sacerdote *sacerdote){
    //entidad->interactuar(this);
}

void EstadoFantasma::interactuar(Banquero *banquero){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::interactuar(Comerciante *comerciante){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::interactuar(Personaje *personaje){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::interactuar(Criatura *criatura){
    //No hacer nada o lanzar excepcion
}
*/
void EstadoFantasma::atacar(Entidad *objetivo, Arma *arma){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::actualizar(double tiempo, Mapa *mapa){
    //No se regenera vida ni mana
    personaje->vidaActual = 0;
    personaje->manaActual = 0;
    Posicion nuevaPosicion = personaje->posicion.mover();
    mapa->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

void EstadoFantasma::recibirDanio(int danio, Entidad *atacante){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::meditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::dejarDeMeditar(){
    //No hacer nada o lanzar excepcion
}


EstadoFantasma::~EstadoFantasma(){}