#include "GameLoop.h"
#include "Operacion.h"

#define MS_POR_ACTUALIZACION (1/100) /*Ver aca que numero poner*/
#define MS_DESCANSO (1/30)

GameLoop::GameLoop(const char* nombreMapa) : colaDeOperaciones(),
                                             mapa(nombreMapa),
                                             continuar(true){}

GameLoop::~GameLoop(){
    //Do nothing
}

/*
static void dormirThread(double previo){
    
    auto actual = std::chrono::system_clock::now();
    double descanso = previo - actual.count();
    double descanso = transcurrido.count();
    if (descanso > MS_DESCANSO) return; // No duermo 
    sleep(MS_DESCANSO - descanso);
    
}
*/

void GameLoop::procesar(){

    auto previo = std::chrono::system_clock::now();
    double lag = 0.0;
    std::chrono::duration<double> transcurrido;
    while (continuar){
        auto actual = std::chrono::system_clock::now();
        transcurrido = actual - previo;
        previo = actual;
        lag += transcurrido.count();
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
        //dormirThread(previo.count());
    }
}

void GameLoop::finalizar(){
    continuar = false;
}


void GameLoop::actualizarPosiciones(){
    /*
    std::string posiciones = mapa.recolectarPosiciones();
    for (cli in clientes){
        cli.enviarPosiciones(posiciones)
    }
    */
}

void GameLoop::procesarOperaciones(){
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



