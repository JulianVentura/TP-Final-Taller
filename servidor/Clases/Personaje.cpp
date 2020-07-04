#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include <utility>
#define VIDA_MAXIMA 50
#define MANA_MAXIMO 100
#define DESPLAZAMIENTO 1.5
#define NIVEL_INICIAL 1

Personaje::Personaje(float x, float y, std::string id) : 
                                       Entidad(id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los campos.
    nivel = NIVEL_INICIAL;
    fuerza = config->obtenerPersonajeFuerzaBase();
    inteligencia = config->obtenerPersonajeInteligenciaBase();
    agilidad = config->obtenerPersonajeAgilidadBase();
    constitucion = config->obtenerPersonajeConstitucionBase();
    vidaMaxima = config->calcularVidaMax(this);
    vidaActual = vidaMaxima;
    manaMaximo = config->calcularManaMax(this);
    manaActual = manaMaximo;
    float ancho = config->obtenerPersonajeAncho();
    float alto = config->obtenerPersonajeAlto();
    posicion = std::move(Posicion(x, y, ancho, alto));
    desplazamiento = config->obtenerPersonajeVelDesplazamiento();
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

void Personaje::curar(unsigned int curVida, unsigned int curMana){
    vidaActual += curVida;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    manaActual += curMana;
    if (manaActual > manaMaximo) manaActual = manaMaximo;
}

void Personaje::eliminarDeInventario(unsigned int pos){
    inventario.eliminar(pos);
}


void Personaje::recibirOro(unsigned int cantOro){
    this->cantidadOro += cantOro;
}


void Personaje::equipar(Arma *arma){
    this->arma = arma;
}

void Personaje::equipar(Armadura *armadura){
    this->armadura = armadura;
}

void Personaje::equipar(Casco *casco){
    this->casco = casco;
}

void Personaje::equipar(Escudo *escudo){
    this->escudo = escudo;
}