#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__
#include "../../common/Thread.h"
#include "Mapa.h"
#include "ColaOperaciones.h"
#include "Reloj.h"
#include <atomic>
#include <map>


class Sala;
class Cliente;
class GameLoop : public Thread{
    private:
    unsigned int msPorActualizacion;
    unsigned int msDescanso;
    ColaOperaciones &colaDeOperaciones;
    Mapa &mapa;
    std::atomic<bool> continuar;
    Reloj reloj;
    Sala &miSala;
    /*
    Procesa todas las operaciones que encuentre en la colaDeOperaciones
    */
    void procesarOperaciones();
    public:
    GameLoop(ColaOperaciones &cola, Mapa &unMapa, Sala &unaSala);
    GameLoop(GameLoop &otro) = delete;
    GameLoop(GameLoop &&otro) = delete;
    GameLoop& operator=(GameLoop &otro) = delete;
    GameLoop& operator=(GameLoop &&otro) = delete;
    virtual ~GameLoop();
    void procesar() override;
    void finalizar();
};

#endif 
