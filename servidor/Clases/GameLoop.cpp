#include "GameLoop.h"
#include "Cliente.h"
#include "Operacion.h"
#include "Sala.h"
#include <random>
#include <iostream> //DEBUG

#define MS_POR_ACTUALIZACION 11 /*Ver aca que numero poner*/
//#define MS_DESCANSO 16.5 // 60 FPS
#define MS_DESCANSO 33 // 30 FPS 

//DEBUG
//#define MS_DESCANSO 200 //Se actualiza 2 veces por segundo
//#define MS_POR_ACTUALIZACION 50

GameLoop::GameLoop(ColaOperaciones &cola, Mapa &unMapa, Sala &unaSala) : 
                                                colaDeOperaciones(cola),
                                                mapa(unMapa),
                                                continuar(true),
                                                reloj(),
                                                miSala(unaSala){}

GameLoop::~GameLoop(){
    //Do nothing
}

void GameLoop::procesar(){
    double lag = 0.0;
    double transcurrido = 0.0;
    try{
        while (continuar){
            transcurrido = reloj.actualizar();
            lag += transcurrido;
            //Proceso las operaciones de la cola
            procesarOperaciones();
            while (lag >= MS_POR_ACTUALIZACION){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(MS_POR_ACTUALIZACION);
                lag -= MS_POR_ACTUALIZACION;
            }
            miSala.actualizarClientes();
            //DEBUG
            //std::cout << "\x1B[2J\x1B[H";
            //std::cout << mapa.aCadena() << std::endl;
            reloj.dormir(MS_DESCANSO);
        }
    }catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch (...){
        std::cerr << "Error desconocido capturado en GameLoop" <<std::endl;
    }
}

void GameLoop::finalizar(){
    continuar = false;
}


void GameLoop::procesarOperaciones(){
    bool continuar = true;
    Operacion* operacionActual;
    while (continuar){
        operacionActual = colaDeOperaciones.pop();
        if (operacionActual){
            operacionActual->ejecutar();
        }else{
            continuar = false;
        }
    }
}
