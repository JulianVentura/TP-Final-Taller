#include "Arma.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Divulgador.h"

Arma::Arma(int unDanioMax, 
           int unDanioMin, 
           unsigned int consMana, 
           float unRadioAtaque, 
           std::string unId,
           uint16_t idTCP, 
           unsigned int unPrecio) : 
           Item(unId, idTCP, unPrecio), 
           danioMax(unDanioMax), 
           danioMin(unDanioMin), 
           consumoMana(consMana), 
           radioAtaque(unRadioAtaque){}

void Arma::atacar(Entidad *objetivo, Entidad *atacante, Divulgador *divulgador){
    float distancia = atacante->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque){
        //Enviar mensaje a atacante : "Estas muy lejos del oponente"
    }
    if (!atacante->manaSuficiente(this->consumoMana)){
        //Enviar mensaje a atacante : "No tenes mana suficiente para realizar el ataque"
        return;
    }
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int danio = configuraciones->calcularDanioAtaque(objetivo, 
                                                              atacante,
                                                              this);
    objetivo->recibirDanio(danio, atacante, divulgador);
    atacante->consumirMana(this->consumoMana);
}


void Arma::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}