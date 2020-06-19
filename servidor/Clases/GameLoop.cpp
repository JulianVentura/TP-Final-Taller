#include "GameLoop.h"
#include "Operacion.h"
#include <random>
#include <iostream> //DEBUG

#define MS_POR_ACTUALIZACION 10 /*Ver aca que numero poner*/
#define MS_DESCANSO 16.5 // 60 FPS
//#define MS_DESCANSO 33 // 30 FPS 

GameLoop::GameLoop(ColaSegura &cola, Mapa &unMapa, Sala &unaSala) : 
                                             colaDeOperaciones(cola),
                                             mapa(unMapa),
                                             continuar(true),
                                             reloj(),
                                             miSala(unaSala),
                                             distribution(5, 20){}

GameLoop::~GameLoop(){
    //Do nothing
}

int GameLoop::simularTrabajo(){
    //std::cout << "Numero random: " << distribution(generator) << std::endl;
    return distribution(generator);
}

void GameLoop::procesar(){
    
    double lag = 0.0;
    double transcurrido = 0.0;
    try{
        while (continuar){
            transcurrido = reloj.actualizar();
            lag += transcurrido;
            std::cout << "FPS: " << (1/transcurrido)*1000 << std::endl;
            //Proceso las operaciones de la cola
            procesarOperaciones();
        
            while (lag >= MS_POR_ACTUALIZACION){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(MS_POR_ACTUALIZACION);
                lag -= MS_POR_ACTUALIZACION;
            }
            //Reordeno el mapa (se actualiza el quadTree)
            //mapa.reordenar();
            actualizarPosiciones();
            reloj.dormir(MS_DESCANSO);
    }
    }catch (const Excepcion &e){
        std::cerr << e.what() << std::endl;
    }
    
}

void GameLoop::finalizar(){
    continuar = false;
}


void GameLoop::actualizarPosiciones(){
    //Simulo trabajo
    //std::this_thread::sleep_for(std::chrono::milliseconds(simularTrabajo()));
    std::string posiciones = mapa.recolectarPosiciones();
    miSala.actualizarClientes(posiciones);
}

void GameLoop::procesarOperaciones(){
    //Simulo trabajo
    //std::this_thread::sleep_for(std::chrono::milliseconds(simularTrabajo()));
    
    bool continuar = true;
    OperacionEncapsulada operacionActual;
    while (continuar){
        try{
            operacionActual = colaDeOperaciones.pop();
            operacionActual.obtenerOperacion()->ejecutar();
        }catch(const ExcepcionColaVacia &e){
            continuar = false;
        }
    }
}




