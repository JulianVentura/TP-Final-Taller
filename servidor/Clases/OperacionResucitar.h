#ifndef __OPERACION_RESUCITAR__
#define __OPERACION_RESUCITAR__
#include "Operacion.h"

class Cliente;
class Mapa;
class OperacionResucitar : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;
    unsigned int posItem;

    public:
    OperacionResucitar(Cliente *cliente, Mapa *mapa);
    ~OperacionResucitar() override;
    void ejecutar() override;
};


/*
Necesito cambiar el estado del personaje a inmovilizado pasandole un lapso de tiempo.
Cuando ese lapso se cumpla se debe ejecutar la teletransportacion del personaje a una nueva zona.

OperacionResucitar::ejecutar(){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    float penalidad = config->calcularPenalidadTiempoResucitar(mapa);
    cliente->obtenerPersonaje()->resucitar(cliente, penalidad);
}


Personaje::resucitar(Cliente *cliente, double penalidad){
    this->estado = std::unique_ptr<Estado>(new EstadoInmovilizado(cliente, penalidad));
}

EstadoInmovilizado::actualizarEstado(double tiempo){
    if (tiempoTranscurrido >= tiempoPenalidad){
        cliente->cambiarDeMapa();
    }
    personaje->estadoNormal();
}
Necesito obtener la penalidad y el mapa al cual teletransportarme.

La penalidad se puede obtener en funcion de la distancia hacia el teletransportador a la ciudad mas cercana.

Si tenemos la posicion del personaje podemos calcular la distancia a la ciudad mas proxima de la sig forma:

Necesitamos la posicion del portal que nos lleva a la ciudad mas proxima, para eso necesitamos el id de la ciudad
mas proxima y el id del mapa actual.

Configuraciones::obtenerPenalizacionRevivir(mapaActual, personaje){
    posPersonaje = personaje->posicion;
    std::string ciudadDestino = this->obtenerCiudadMasCercana();

    //Iterar sobre los portales del mapa actual y encontrar el que lleva a ciudadDestino 
    std::string idPortalDestino = //Iterar.
    Entidad *portalDestino = mapaActual->obtener(idPortalDestino);
    double distancia = posPersonaje.calcularDistancia(portalDestino->obtenerPosicion());
    return 10000 + distancia * 1000;
}

*/

#endif