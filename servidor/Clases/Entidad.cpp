#include "Entidad.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Criatura.h"
#include "BolsaDeItems.h"
#include "Excepcion.h"
#include <vector>

Entidad::Entidad(std::string unId) : 
                 Posicionable(0, 0, 0, 0),
                 vidaMaxima(0),
                 vidaActual(0),
                 manaMaximo(0),
                 manaActual(0),
                 fuerza(0),
                 inteligencia(0),
                 agilidad(0),
                 constitucion(0),
                 nivel(0),
                 id(unId),
                 arma(nullptr),
                 inventario(),
                 mapaAlQuePertenece(nullptr){}


const quadtree::Box<float>& Entidad::obtenerArea() const{
    return posicion.obtenerAreaQueOcupa();
}

bool Entidad::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Entidad::colisionaCon(const quadtree::Box<float> &area) const{
    return posicion.obtenerAreaQueOcupa().intersects(area);
}
const std::string Entidad::obtenerId() const{
    return std::move(id);
}

void Entidad::actualizarEstado(double tiempo, Mapa *mapa){
    Posicion nuevaPosicion = posicion.mover();
    mapa->actualizarPosicion(this, std::move(nuevaPosicion));
}


void Entidad::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    this->vidaActual -= danio;
    unsigned int experiencia = configuraciones->calcularExpPorGolpe(this,
                                                                    atacante,
                                                                    danio);
    atacante->obtenerExperiencia(experiencia);
    //Enviar mensaje a this : "Recibes " << danio << "de daño";
    //Enviar mensaje a atacante : "Realizas " << danio << "de daño";
    if (vidaActual <= 0){
        //Enviar mensaje a this : "Has muerto";
        experiencia = configuraciones->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(experiencia);
        dropearItems(atacante);
    }
}

void Entidad::consumirMana(unsigned int cantidad){
    if ((manaActual - cantidad) < 0){
        throw Excepcion("No hay mana suficiente");
    }
    manaActual -= cantidad;
}

bool Entidad::manaSuficiente(unsigned int cantidad){
    if ((manaActual - cantidad) < 0) return false;
    return true;
}

void Entidad::obtenerExperiencia(unsigned int cantidad){
    //Do nothing
}

void Entidad::equipar(Arma *unArma){
    arma = unArma;
}

void Entidad::recibirOro(unsigned int cantidad){
    //Do nothing
}

void Entidad::almacenar(Item *item){
    //Guarda que si falla se pierde el item.
    inventario.almacenar(item);
}

void Entidad::indicarMapaAlQuePertenece(Mapa *mapa){
    this->mapaAlQuePertenece = mapa;
}

Entidad::~Entidad(){}


/*
Estados:

Pacifico:

Es el estado de los Ciudadanos, no pueden ser atacados ni atacar pero si pueden comerciar.

Normal:

En este estado no hay restriccion de ningun tipo, se puede comerciar y atacar.

Meditacion:

En este estado no se puede comerciar, atacar, ni moverse, pero aumenta la regeneracion de vida y mana.

Fantasma:

En este estado solo se puede interactuar con un sanador o ejecutar el comando /resucitar

*/


/*
Ejemplo de codigo:

Entidad::atacar(id){
    Entidad *entidad = mapa.obtenerEntidad(id);
    estado.atacar(entidad);
}

Estado::atacar(entidad){
    //Aca puedo tirar una excepcion si estoy en un estado donde no puedo atacar.
    duenio->arma->atacar(entidad);
}

Ciudadano::interactuar(Personaje *personaje){
    personaje->interactuar(this);
}

Entidad::interactuar(){

}

El estado ademas se encarga del movimiento y de la regeneracion.

Entidad::actualizarEstado(tiempo){
    estado->actualizar(tiempo);
}

Estado::actualizar(tiempo){
    //Esto puede cambiar si es en meditacion, se hace un llamado a otro metodo
    unsigned int regenVida = config->calcularPersonajeRegenVida(personaje, tiempo);
    unsigned int regenMana = config->calcularPersonajeRegenMana(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    personaje->actualizarPosicion();
}

Profundizacion de como seria la interaccion entre las entidades:

Personaje::interactuar(id){
    Entidad *entidad = mapa.obtenerEntidad(id);
    entidad.interactuar(&estado);
}

Fantasma::interactuar(Banquero *banquero){
    //Lanzo excepcion
}

Fantasma::interactuar(Personaje *personaje){
    //Lanzo excepcion
}

Fantasma::interactuar(Criatura *criatura){
    //Lanzo excepcion
}

Fantasma::interactuar(Comerciante *comerciante){
    //Lanzo excepcion
}

Fantasma::interactuar(Sacerdote *sacerdote){
    personaje->cambiarEstado(Normal(personaje));
}

Banquero::interactuar(Estado *estado){
    estado->interactuar(this);
}


Entonces un estado tiene que permitir:

- interactuar
- atacar
- mover

*/