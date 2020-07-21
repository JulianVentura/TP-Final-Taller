#include "BuclePrincipal.h"
#include "Cliente.h"
#include "Operacion.h"
#include "Sala.h"
#include <iostream>


BuclePrincipal::BuclePrincipal(ColaOperaciones &cola, Mapa &unMapa, Sala &unaSala) : 
                                                msPorActualizacion(0),
                                                msDescanso(0),
                                                colaDeOperaciones(cola),
                                                mapa(unMapa),
                                                continuar(true),
                                                reloj(),
                                                miSala(unaSala){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    msPorActualizacion = config->obtenerBuclePrincipalMSporActualizacion();
    msDescanso = config->obtenerBuclePrincipalMSdescanso();
}

BuclePrincipal::~BuclePrincipal(){}

void BuclePrincipal::procesar(){
    double lag = 0.0;
    double transcurrido = 0.0;
    while (continuar){
        try{
            transcurrido = reloj.actualizar();
            lag += transcurrido;
            //Proceso las operaciones de la cola
            procesarOperaciones();
            while (lag >= msPorActualizacion){
                //Esto puede implicar un movimiento en el mapa
                mapa.entidadesActualizarEstados(msPorActualizacion);
                lag -= msPorActualizacion;
            }
            miSala.actualizarClientes(transcurrido);
            miSala.persistirClientes(transcurrido);
            reloj.dormir(msDescanso);
        }catch(const Excepcion &e){
            //No me interesa reportar una excepcion mia, se que no implica un problema grave.
            //Por esa misma razon no quiero cortar el ciclo.
            std::cerr << e.what() << std::endl;
        }catch (const std::exception &e){
            //Si quiero notificar de una excepcion mas general y cortar el ciclo.
            std::cerr << e.what() << std::endl;
            continuar = false;
        }catch (...){
            std::cerr << "Error desconocido capturado en BuclePrincipal" <<std::endl;
            continuar = false;
        }
    }   
}

void BuclePrincipal::finalizar(){
    continuar = false;
}


void BuclePrincipal::procesarOperaciones(){
    bool seguirIterando = true;
    Operacion* operacionActual;
    while (seguirIterando){
        try{
            operacionActual = colaDeOperaciones.pop();
            if (operacionActual){
                operacionActual->ejecutar();
            }else{
                seguirIterando = false;
            }
        }catch(const Excepcion &e){
            //No me interesa imprimir mensajes de excepcion, tampoco cortar el ciclo.
        }catch(const std::exception &e){
            //Si otras excepciones mas generales, pueden indicar errores de memoria por ejemplo.
            std::cerr << e.what() << std::endl;
            seguirIterando = false;
        }catch(...){
            std::cerr << "Error desconocido capturado en BuclePrincipal" << std::endl;
            seguirIterando = false;
        }
    }
}
