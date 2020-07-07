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
    std::string id = "EstadoNormal";
    idTCP = config->obtenerEstadoIDTCP(id);
}

void EstadoFantasma::interactuar(Entidad *entidad){
    //Interactuar normalmente.
}

void EstadoFantasma::atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador){
    //Enviar mensaje: "No se puede atacar siendo fantasma"
}

void EstadoFantasma::actualizar(double tiempo, Mapa *mapa){
    //No se regenera vida ni mana
    personaje->vidaActual = 0;
    personaje->manaActual = 0;
    Posicion nuevaPosicion = personaje->posicion.mover();
    mapa->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

void EstadoFantasma::serAtacadoPor(Entidad *atacante, Divulgador *divulgador){
    //Enviar mensaje: "No se puede entrar en pelea siendo fantasma"
}

void EstadoFantasma::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    //Enviar mensaje: "No se puede entrar en pelea siendo fantasma"
}

void EstadoFantasma::meditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoFantasma::dejarDeMeditar(){
    //No hacer nada o lanzar excepcion
}


void EstadoFantasma::pedirCuracion(Sacerdote *sacerdote, Cliente *cliente){
    sacerdote->curar(personaje, cliente);
    personaje->estadoNormal();
}

void EstadoFantasma::pedirListado(Interactuable *interactuable, Cliente *cliente){
    //No hacer nada
}

void EstadoFantasma::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    //No hacer nada
}

void EstadoFantasma::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    //No hacer nada
}

EstadoFantasma::~EstadoFantasma(){}