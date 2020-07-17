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



*/

#endif