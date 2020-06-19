#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__
#include "Thread.h"
#include "Mapa.h"
#include "ColaSegura.h"
#include "Reloj.h"
#include "Cliente.h"
#include "Sala.h"
#include <atomic>
#include <random> //DEBUG
#include <map>


class GameLoop : public Thread{

    private:
    ColaSegura &colaDeOperaciones;
    Mapa &mapa;
    std::atomic<bool> continuar;
    Reloj reloj;
    Sala &miSala;

    //DEBUG
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    int simularTrabajo();
    /*
    Le enviara a cada cliente conectado a la sala las posiciones
    de las entidades en el mapa, ademas de 
    */
    void actualizarPosiciones();
    /*
    Procesa todas las operaciones que encuentre en la colaDeOperaciones
    */
    void procesarOperaciones();
    public:
    GameLoop(ColaSegura &cola, Mapa &unMapa, Sala &unaSala);
    GameLoop(GameLoop &otro) = delete;
    GameLoop(GameLoop &&otro) = delete;
    GameLoop& operator=(GameLoop &otro) = delete;
    GameLoop& operator=(GameLoop &&otro) = delete;
    virtual ~GameLoop();
    void procesar() override;
    void finalizar();
};

#endif 