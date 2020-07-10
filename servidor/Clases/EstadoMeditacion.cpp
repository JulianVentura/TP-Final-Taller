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

void EstadoMeditacion::atacar(Entidad *objetivo, Arma *arma){
    /*
    std::string mensaje = "No puede atacar mientras medita";
    divulgador->encolarMensaje(personaje->id, mensaje);
    */
}

bool EstadoMeditacion::recibirDanio(int danio, Entidad *atacante){
    //Se puede recibir daño en modo meditacion
    return personaje->_recibirDanio(danio, atacante);
}

void EstadoMeditacion::serAtacadoPor(Entidad *atacante){
    atacante->atacar(personaje);
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
    unsigned int regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    unsigned int regenMana = config->calcularRecupManaMeditacion(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    //El personaje no se puede mover
}

//Comerciar

void EstadoMeditacion::interactuar(Entidad *entidad){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::pedirCuracion(Sacerdote *sacerdote, Cliente *cliente){
    std::string mensaje = "No puede interactuar mientras medita";
    cliente->enviarChat(mensaje, false);
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