#include "Arma.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Mapa.h"
#include "Proyectil.h"

Arma::Arma(int unDanioMax, 
           int unDanioMin, 
           unsigned int consMana, 
           float unRadioAtaque, 
           double unTiempoAtaque,
           std::string unId,
           std::string idProyectil,
           uint16_t idTCP, 
           unsigned int unPrecio) : 
           Item(unId, idTCP, unPrecio), 
           danioMax(unDanioMax), 
           danioMin(unDanioMin), 
           consumoMana(consMana),
           proyectil(idProyectil), 
           radioAtaque(unRadioAtaque),
           tiempoAtaque(unTiempoAtaque),
           tiempoTranscurrido(0){}

std::string Arma::atacar(Entidad *objetivo, Entidad *atacante, Mapa *mapa){
    tiempoTranscurrido += reloj.actualizar();
    if (tiempoTranscurrido < tiempoAtaque) return "";
    tiempoTranscurrido = 0;
    if (atacante == objetivo) return "";
    float distancia = atacante->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque){
        return "Estas muy lejos del oponente";
    }
    if (!atacante->manaSuficiente(this->consumoMana)){
        return "No tenes mana suficiente para realizar el ataque";
    }
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int danio = configuraciones->calcularDanioAtaque(objetivo, 
                                                              atacante,
                                                              this);
    atacante->consumirMana(this->consumoMana);
    std::string mensaje = std::move(objetivo->recibirDanio(danio, atacante));
    
    std::unique_ptr<Entidad> proyectil(new Proyectil(this->proyectil, 
                                                         atacante->obtenerPosicion(), 
                                                         objetivo->obtenerPosicion()));
    mapa->cargarEntidadNoColisionable(std::move(proyectil));
    
    return mensaje;
}


void Arma::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this, pos);
}

void Arma::desequipar(Personaje *personaje, unsigned int pos){
    personaje->desequipar(this, pos);
}
