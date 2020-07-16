#include "EstadoFantasma.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Arma.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Interactuable.h"
#include "Sacerdote.h"
#include "Cliente.h"
#include "Item.h"
#include "Divulgador.h"

EstadoFantasma::EstadoFantasma(Personaje *unPersonaje) : Estado(unPersonaje){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id = "EstadoFantasma";
    idTCP = config->obtenerEstadoIDTCP(id);
}

//Ataque

std::string EstadoFantasma::atacar(Entidad *objetivo, Arma *arma){
    return "No se puede atacar siendo fantasma";
}

std::string EstadoFantasma::serAtacadoPor(Entidad *atacante){
    return "No puede atacar a un fantasma";
}

//Otras acciones

void EstadoFantasma::meditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::dejarDeMeditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::actualizar(double tiempo){
    //No se regenera vida ni mana
    personaje->vidaActual = 0;
    personaje->manaActual = 0;
    Posicion nuevaPosicion = personaje->posicion.mover(tiempo);
    personaje->mapaAlQuePertenece->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

//Comercio

void EstadoFantasma::interactuar(Entidad *entidad){
    //Interactuar normalmente.
}

void EstadoFantasma::curar(float curVida, float curMana){
    personaje->curar(curVida, curMana);
    personaje->estadoNormal();
}

void EstadoFantasma::pedirListado(Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarChat(mensaje, false);
}

void EstadoFantasma::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarChat(mensaje, false);
}

void EstadoFantasma::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarChat(mensaje, false);
}

EstadoFantasma::~EstadoFantasma(){}