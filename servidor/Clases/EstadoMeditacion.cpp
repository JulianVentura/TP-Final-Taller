#include "EstadoMeditacion.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Arma.h"
#include "Mapa.h"
#include "Configuraciones.h"

EstadoMeditacion::EstadoMeditacion(Personaje *unPersonaje) : Estado(unPersonaje){}

void EstadoMeditacion::interactuar(Entidad *entidad){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::atacar(Entidad *objetivo, Arma *arma){
    //No hacer nada o lanzar excepcion
}

void EstadoMeditacion::actualizar(double tiempo, Mapa *mapa){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    unsigned int regenMana = config->calcularRecupManaMeditacion(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    //El personaje no se puede mover
}

void EstadoMeditacion::recibirDanio(int danio, Entidad *atacante){
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

void EstadoMeditacion::meditar(){
    //Do nothing
}

void EstadoMeditacion::dejarDeMeditar(){
    personaje->estadoNormal();
}

EstadoMeditacion::~EstadoMeditacion(){}