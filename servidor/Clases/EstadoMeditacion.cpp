#include "EstadoMeditacion.h"
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

//Comerciar

void EstadoMeditacion::interactuar(Entidad *entidad){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::curar(float curVida, float curMana){
    //No hace nada.
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

EstadoMeditacion::~EstadoMeditacion(){}