#include "Arma.h"
#include "Entidad.h"

Arma::Arma(unsigned int unDanioMax, unsigned int unDanioMin, float unRadioAtaque) : 
           danioMax(unDanioMax), danioMin(unDanioMin), radioAtaque(unRadioAtaque){}

void Arma::atacar(Entidad *objetivo, Entidad *atacante){
    float distancia = atacante->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque) return;
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int danio = configuraciones->calcularDanioAtaque(objetivo, 
                                                              atacante,
                                                              this);
    objetivo->recibirDanio(danio, atacante);
}