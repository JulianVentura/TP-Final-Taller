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
    std::string id = "EstadoNormal";
    idTCP = config->obtenerEstadoIDTCP(id);
}

void EstadoMeditacion::interactuar(Entidad *entidad){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::actualizar(double tiempo, Mapa *mapa){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    unsigned int regenMana = config->calcularRecupManaMeditacion(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    //El personaje no se puede mover
}

void EstadoMeditacion::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    //Se puede recibir daño en modo meditacion
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    personaje->vidaActual -= danio;
    unsigned int exp = configuraciones->calcularExpPorGolpe(personaje, atacante, danio);
    atacante->obtenerExperiencia(exp);
    if (personaje->vidaActual <= 0){
        exp = configuraciones->calcularExpPorMatar(personaje, atacante);
        atacante->obtenerExperiencia(exp);
        personaje->dropearItems(atacante);
        personaje->estadoFantasma();
    }
}

void EstadoMeditacion::serAtacadoPor(Entidad *atacante, Divulgador *divulgador){
    atacante->atacar(personaje, divulgador);
}

void EstadoMeditacion::meditar(){
    //Do nothing
}

void EstadoMeditacion::dejarDeMeditar(){
    personaje->estadoNormal();
}

void EstadoMeditacion::pedirCuracion(Sacerdote *sacerdote, Cliente *cliente){
    //No se puede interactuar en estado de meditacion
}

void EstadoMeditacion::pedirListado(Interactuable *interactuable, Cliente *cliente){
    //No se puede interactuar en estado de meditacion
}

void EstadoMeditacion::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    //No se puede interactuar en estado de meditacion
}

void EstadoMeditacion::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    //No se puede interactuar en estado de meditacion
}

EstadoMeditacion::~EstadoMeditacion(){}