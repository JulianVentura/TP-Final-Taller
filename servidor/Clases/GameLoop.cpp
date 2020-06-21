#include "GameLoop.h"
#include "Cliente.h"
#include "Operacion.h"
#include "Sala.h"
#include <random>
#include <iostream> //DEBUG

#define MS_POR_ACTUALIZACION 50 /*Ver aca que numero poner*/
//#define MS_DESCANSO 16.5 // 60 FPS
//#define MS_DESCANSO 33 // 30 FPS 
#define MS_DESCANSO 200 //Se actualiza 2 veces por segundo

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
            //std::cout << "FPS: " << (1/transcurrido)*1000 << std::endl;
            //Proceso las operaciones de la cola
            procesarOperaciones();
            while (lag >= MS_POR_ACTUALIZACION){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(MS_POR_ACTUALIZACION);
                lag -= MS_POR_ACTUALIZACION;
            }
            miSala.actualizarClientes();
            //DEBUG
            std::cout << "\x1B[2J\x1B[H";
            std::cout << mapa.aCadena() << std::endl;
            reloj.dormir(MS_DESCANSO);
        }
    }catch (const Excepcion &e){
        std::cerr << e.what() << std::endl;
    }catch (...){
        std::cerr << "Error desconocido capturado en GameLoop" <<std::endl;
    }
}

void GameLoop::finalizar(){
    continuar = false;
}


void GameLoop::procesarOperaciones(){
    //Simulo trabajo
    //std::this_thread::sleep_for(std::chrono::milliseconds(simularTrabajo()));
    bool continuar = true;
    OperacionEncapsulada operacionActual;
    /*
    TODO:
    Pensar bien en esto, quizas no conviene lanzar una excepcion en cada iteracion
    del gameloop, puede llegar a ser muy caro.
    Quizas se puede hacer un nuevo tipo de cola que contenga *operacion y que se encargue
    de liberarlas a medida que las van sacando de la cola.
    Cuando se pide un nuveo elemento de la cola se puede liberar al anterior.
    De esta forma cuando la cola se queda sin elementos puede devolver nullptr, no hay necesidad
    de usar excepciones.
    Se puede implementar utilizando una std::queue<Operacion*> y un puntero a la ultima operacion
    extraida, que sera liberada cuando se vuelva a llamar al metodo pop() 
    Ademas no se pierde memoria dinamica y ya no seria necesaria la clase OperacionEncapsulada.
    */
    while (continuar){
        try{
            operacionActual = colaDeOperaciones.pop();
            operacionActual.obtenerOperacion()->ejecutar();
        }catch(const ExcepcionColaVacia &e){
            continuar = false;
        }
    }
}
