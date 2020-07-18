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
            //Descomentar para ver FPS
            //fprintf(stderr, "FPS: %f\n", 1000/transcurrido);
            //Proceso las operaciones de la cola
            procesarOperaciones();
            while (lag >= msPorActualizacion){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(msPorActualizacion);
                lag -= msPorActualizacion;
            }
            miSala.actualizarClientes(transcurrido);
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
    bool seguirIterando = true;
    Operacion* operacionActual;
    while (seguirIterando){
        operacionActual = colaDeOperaciones.pop();
        if (operacionActual){
            operacionActual->ejecutar();
        }else{
            seguirIterando = false;
        }
    }
}

/*

Almacenero guarda oro:

Nueva operacion CODIGO_TRANSFERIR que recibe un id y un monto con signo.

Se ira a buscar a tal id al mapa y se le solicitara tal operacion:


OperacionTransferir::ejecutar(mapa, cliente, id, monto){
    Entidad *entidad = mapa->buscar(id);
    Personaje *personaje = cliente->obtenerPersonaje();

    entidad->solicitarTransferencia(personaje->estado(), cliente, monto);
}

Banquero::solicitarTransferencia(estado, cliente, monto){
    estado->pedirTransferencia(this, monto, cliente);
}

EstadoNormal::pedirTransferencia(banquero, monto, cliente){
    banquero->transferir(this->personaje, monto, cliente);
}
//Monto > 0 : El banquero recibe dinero
//Monto <= 0 : El banquero entrega dinero
Banquero::transferir(personaje, cliente, monto){
    if (monto >= 0){
        if (personaje->oroAlmacenado < monto){
            //No tiene oro suficiente.
        }
    }
}

*/