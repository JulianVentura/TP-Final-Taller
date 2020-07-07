#include "Arma.h"
#include "Entidad.h"
#include "Personaje.h"

Arma::Arma(int unDanioMax, 
           int unDanioMin, 
           unsigned int consMana, 
           float unRadioAtaque, 
           std::string unId, 
           unsigned int unPrecio) : 
           Item(unId, unPrecio), 
           danioMax(unDanioMax), 
           danioMin(unDanioMin), 
           consumoMana(consMana), 
           radioAtaque(unRadioAtaque){}

void Arma::atacar(Entidad *objetivo, Entidad *atacante){
    float distancia = atacante->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque) return;      //Ver si hay que enviar algun mensaje al cliente
    atacante->consumirMana(this->consumoMana);      //Esto debe lanzar una excepcion si falla, para que no se ejecute el ataque.
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int danio = configuraciones->calcularDanioAtaque(objetivo, 
                                                              atacante,
                                                              this);
    objetivo->recibirDanio(danio, atacante);
}


void Arma::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}