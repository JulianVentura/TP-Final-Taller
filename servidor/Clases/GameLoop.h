#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__
#include "Thread.h"
#include "Mapa.h"
#include "ColaBloqueante.h"
#include <atomic>

class GameLoop : Thread{

    private:
    ColaBloqueante colaDeOperaciones;
    Mapa mapa;
    std::atomic<bool> continuar;
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
    GameLoop(const char* nombreMapa);
    GameLoop(GameLoop &otro) = delete;
    GameLoop(GameLoop &&otro) = delete;
    GameLoop& operator=(GameLoop &otro) = delete;
    GameLoop& operator=(GameLoop &&otro) = delete;
    virtual ~GameLoop();
    void procesar() override;
    void finalizar();
};

#endif 