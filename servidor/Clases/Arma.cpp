#include "Arma.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Divulgador.h"
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

void Arma::atacar(Entidad *objetivo, Entidad *atacante, Mapa *mapa){
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    tiempoTranscurrido += reloj.actualizar();
    if (tiempoTranscurrido < tiempoAtaque) return;
    tiempoTranscurrido = 0;

    float distancia = atacante->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque){
        std::string mensaje = "Estas muy lejos del oponente";
        divulgador->encolarMensaje(atacante->obtenerId(), mensaje);
        return;
    }
    if (!atacante->manaSuficiente(this->consumoMana)){
        std::string mensaje = "No tenes mana suficiente para realizar el ataque";
        divulgador->encolarMensaje(atacante->obtenerId(), mensaje);
        return;
    }
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int danio = configuraciones->calcularDanioAtaque(objetivo, 
                                                              atacante,
                                                              this);
    if (objetivo->recibirDanio(danio, atacante)){
        atacante->consumirMana(this->consumoMana);
        /*
        std::unique_ptr<Entidad> proyectil(new Proyectil(this->proyectil, 
                                                         atacante->obtenerPosicion(), 
                                                         objetivo->obtenerPosicion()));
        mapa->cargarEntidadNoColisionable(std::move(proyectil));
        */
    }
}


void Arma::utilizar(Personaje *personaje, unsigned int pos){
    personaje->equipar(this);
}

void Arma::desequipar(Personaje *personaje){
    personaje->equipar(this);
}
