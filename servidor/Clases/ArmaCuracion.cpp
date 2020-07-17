#include "ArmaCuracion.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Mapa.h"
#include "Proyectil.h"
#include <sstream>

ArmaCuracion::ArmaCuracion(int curMax, 
                           int curMin, 
                           unsigned int consMana, 
                           float radioAtaque,
                           double tiempoAtaque, 
                           std::string id,
                           std::string idProyectil,
                           uint16_t idTCP,
                           unsigned int unPrecio) : 
                           Arma(curMax, 
                                curMin, 
                                consMana, 
                                radioAtaque, 
                                tiempoAtaque, 
                                id, 
                                idProyectil, 
                                idTCP, 
                                unPrecio){}

std::string ArmaCuracion::atacar(Entidad *objetivo, Entidad *lanzador, Mapa *mapa){
    tiempoTranscurrido += reloj.actualizar();
    if (tiempoTranscurrido < tiempoAtaque) return "";
    tiempoTranscurrido = 0;

    float distancia = lanzador->obtenerPosicion().calcularDistancia(objetivo->obtenerPosicion());
    if (distancia > this->radioAtaque){
        return "Estas muy lejos del objetivo";
    }
    if (!lanzador->manaSuficiente(this->consumoMana)){
        return "No tenes mana suficiente";
    }
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    unsigned int curacion = configuraciones->calcularCuracion(objetivo, 
                                                              lanzador,
                                                              this);
    lanzador->consumirMana(this->consumoMana);
    objetivo->recibirCuracion(curacion, lanzador);
    
    std::unique_ptr<Entidad> proyectil(new Proyectil(this->proyectil, 
                                                     lanzador->obtenerPosicion(), 
                                                     objetivo->obtenerPosicion()));
    mapa->cargarEntidadNoColisionable(std::move(proyectil));
    if (objetivo == lanzador){
        return "";
    }
    std::stringstream mensaje;
    mensaje << "Has curado " << curacion << " puntos de vida al objetivo";
    return mensaje.str();
}
