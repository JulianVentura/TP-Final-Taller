#include "EstadoMeditacion.h"
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

EstadoMeditacion::EstadoMeditacion(Personaje *unPersonaje) : Estado(unPersonaje){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id = "EstadoMeditacion";
    idTCP = config->obtenerEstadoIDTCP(id);
}

//Ataque

std::string EstadoMeditacion::atacar(Entidad *objetivo, Arma *arma){
    return "No puede atacar mientras medita";
}

std::string EstadoMeditacion::serAtacadoPor(Entidad *atacante){
    return std::move(atacante->atacar(personaje));
}

//Otras acciones

void EstadoMeditacion::meditar(){
    //Do nothing
}

void EstadoMeditacion::dejarDeMeditar(){
    personaje->estadoNormal();
}

void EstadoMeditacion::actualizar(double tiempo){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    float regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    float regenMana = config->calcularRecupManaMeditacion(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    if (personaje->manaActual == personaje->manaMaximo){
        personaje->estadoNormal();
    }
    //El personaje no se puede mover
}

void EstadoMeditacion::resucitar(double tiempo){
    throw Excepcion("Se ha solicitado resureccion en estado meditacion");
}

//Comerciar

void EstadoMeditacion::interactuar(Entidad *entidad){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::sanar(){
    //Nada
}

bool EstadoMeditacion::curar(float curVida, float curMana){
    return false;
}

void EstadoMeditacion::pedirListado(Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede interactuar mientras medita";
    cliente->enviarChat(mensaje, false);
}

void EstadoMeditacion::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede interactuar mientras medita";
    cliente->enviarChat(mensaje, false);
}

void EstadoMeditacion::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    std::string mensaje = "No puede interactuar mientras medita";
    cliente->enviarChat(mensaje, false);
}

void EstadoMeditacion::pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero){
    std::string mensaje = "No puede realizar una transaccion mientras medita";
    cliente->enviarChat(mensaje, false);
}

EstadoMeditacion::~EstadoMeditacion(){}