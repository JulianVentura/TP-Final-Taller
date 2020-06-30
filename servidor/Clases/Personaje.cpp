#include "Personaje.h"
#include "Mapa.h"
#include <utility>
#define DESPLAZAMIENTO 0.25
#define NIVEL_INICIAL 1

Personaje::Personaje(float x, float y, std::string id) : 
                                       Entidad(0,
                                               0,
                                               0,
                                               NIVEL_INICIAL,
                                               x,
                                               y,
                                               id){
    actualizarAtributos();
    agilidad = 2; //Cambiar
    desplazamiento = DESPLAZAMIENTO;
}
Personaje& Personaje::operator=(Personaje &&otro){
    this->vidaActual = otro.vidaActual;
    this->manaActual = otro.manaActual;
    this->vidaMaxima = otro.vidaMaxima;
    this->manaMaximo = otro.manaMaximo;
    this->agilidad   = otro.agilidad;
    this->nivel      = otro.nivel;
    this->experiencia = otro.experiencia;
    this->limiteParaSubir = otro.limiteParaSubir;
    this->id = std::move(otro.id);
    this->posicion = std::move(otro.posicion);
    this->desplazamiento = otro.desplazamiento;
    //No hay necesidad de modificar a "otro", no puede haber ningun problema.
    return *this;
}
Personaje::~Personaje(){}


void Personaje::actualizarAtributos(){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    vidaMaxima = configuraciones->calcularVidaMax(this);
    manaMaximo = configuraciones->calcularManaMax(this);
    limiteParaSubir = configuraciones->calcularLimiteParaSubir(this);
}

void Personaje::obtenerExperiencia(unsigned int cantidad){
    experiencia += cantidad;
    if (experiencia >= limiteParaSubir){
        nivel++;
        actualizarAtributos();
    }
}

void Personaje::actualizarEstado(double tiempo, Mapa *mapa){
    /* Actualizar estado */
    /*
    1- Regenerar vida
    2- Regenerar mana
    3- Moverse
    */
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    //Ver como cambia esto con la meditacion.
    //Regenerar
    unsigned int regenVida = configuraciones->calcularRecuperacionVida(this, tiempo);
    unsigned int regenMana = configuraciones->calcularRecupManaTiempo(this, tiempo);
    vidaActual += regenVida;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    manaActual += regenMana;
    if (manaActual > manaMaximo) manaActual = manaMaximo;
    //Mover
    Posicion nuevaPosicion = posicion.mover();
    mapa->actualizarPosicion(this, std::move(nuevaPosicion));
}