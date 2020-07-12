#include "GameLoop.h"
#include "Cliente.h"
#include "Operacion.h"
#include "Sala.h"
#include <random>
#include <iostream> //DEBUG


GameLoop::GameLoop(ColaOperaciones &cola, Mapa &unMapa, Sala &unaSala) : 
                                                msPorActualizacion(0),
                                                msDescanso(0),
                                                colaDeOperaciones(cola),
                                                mapa(unMapa),
                                                continuar(true),
                                                reloj(),
                                                miSala(unaSala){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    msPorActualizacion = config->obtenerGameLoopMSporActualizacion();
    msDescanso = config->obtenerGameLoopMSdescanso();
}

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
            while (lag >= msPorActualizacion){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(msPorActualizacion);
                lag -= msPorActualizacion;
            }
            mapa.cargarCriatura();
            miSala.actualizarClientes();
            reloj.dormir(msDescanso);
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
