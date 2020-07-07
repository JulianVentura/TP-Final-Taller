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

void EstadoFantasma::interactuar(Entidad *entidad){
    //Interactuar normalmente.
}

void EstadoFantasma::atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador){
    std::string mensaje = "No se puede atacar siendo fantasma";
    divulgador->encolarMensaje(personaje->id, mensaje);
}

void EstadoFantasma::actualizar(double tiempo, Mapa *mapa){
    //No se regenera vida ni mana
    personaje->vidaActual = 0;
    personaje->manaActual = 0;
    Posicion nuevaPosicion = personaje->posicion.mover();
    mapa->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

void EstadoFantasma::serAtacadoPor(Entidad *atacante, Divulgador *divulgador){
    std::string mensaje = "No puede atacar a un fantasma";
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje);
}

void EstadoFantasma::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    std::string mensaje = "No puede atacar a un fantasma";
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje);
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