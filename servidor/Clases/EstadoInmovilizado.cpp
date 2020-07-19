#include "EstadoInmovilizado.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Arma.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Interactuable.h"
#include "Banquero.h"
#include "Cliente.h"
#include "Item.h"
#include "Divulgador.h"

EstadoInmovilizado::EstadoInmovilizado(Personaje *unPersonaje, 
                                       double pen) : 
                                       Estado(unPersonaje),
                                       penalizacion(pen),
                                       tiempoTranscurrido(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id = "EstadoInmovilizado";
    //Quiero que el estado inmovilizado se vea como un estado fantasma fuera de esta clase.
    std::string id_representacion = "EstadoFantasma";
    idTCP = config->obtenerEstadoIDTCP(id_representacion);
}
//Ataque

std::string EstadoInmovilizado::atacar(Entidad *objetivo, Arma *arma){
    return "No se puede atacar siendo fantasma";
}

std::string EstadoInmovilizado::serAtacadoPor(Entidad *atacante){
    return "No puede atacar a un fantasma";
}

//Otras acciones

void EstadoInmovilizado::meditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoInmovilizado::dejarDeMeditar(){
    //No hacer nada o lanzar excepcion
}

void EstadoInmovilizado::actualizar(double tiempo){
    //No se regenera vida ni mana
    personaje->vidaActual += tiempo * personaje->vidaMaxima / penalizacion;
    personaje->manaActual = 0;
    if (personaje->vidaActual >= personaje->vidaMaxima){
        personaje->vidaActual = personaje->vidaMaxima;
        personaje->estadoNormal();
    }
    //El jugador permanece inmovil como penalizacion de tiempo.

}

void EstadoInmovilizado::resucitar(double tiempo){
    throw Excepcion("Se ha solicitado resureccion en estado inmovilizado");
}

//Comercio

void EstadoInmovilizado::interactuar(Entidad *entidad){
    //Interactuar normalmente.
}

void EstadoInmovilizado::sanar(){
    personaje->curar(personaje->vidaMaxima, personaje->manaMaximo);
    personaje->estadoNormal();
}

bool EstadoInmovilizado::curar(float curVida, float curMana){
    return false;
}

void EstadoInmovilizado::pedirListado(Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarMensaje(mensaje, false);
}

void EstadoInmovilizado::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarMensaje(mensaje, false);
}

void EstadoInmovilizado::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede comerciar siendo fantasma";
    cliente->enviarMensaje(mensaje, false);
}

void EstadoInmovilizado::pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero){
    std::string mensaje = "No puede realizar una transaccion siendo fantasma";
    cliente->enviarMensaje(mensaje, false);
}

EstadoInmovilizado::~EstadoInmovilizado(){}