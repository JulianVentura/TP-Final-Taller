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
    /*
    Ejecuta la operacion de resucitacion, en la cual se teletransportara al personaje a la ciudad
    mas cercana, tras lo cual debera cumplir un tiempo de penalizacion hasta ser revivido.
    */
    void ejecutar() override;
};

#endif