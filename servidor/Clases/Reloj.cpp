#include "Reloj.h"
#include <thread>
#include <iostream>
/*
Convierto la unidad de chrono (nanosegundos) a milisegundos.
*/
#define CONVERSION 1000
#define MILI_A_NANO 1000000


Reloj::Reloj(){
    previo = std::chrono::system_clock::now();
    actual = previo;
    periodo = std::chrono::system_clock::duration::period::den;
}

double Reloj::tiempoTranscurrido(){
    actual = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> transcurrido = (actual - previo);
    return transcurrido.count();
}

double Reloj::actualizar(){
    //No llamo a Reloj::tiempoTranscurrido para no perder precision (tardaria mas)
    actual = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> transcurrido = (actual - previo);
    double resultado = transcurrido.count();
    previo = actual;
    return resultado;
}

void Reloj::dormir(double tiempo){
    //Lo convierto a nanosegundos
    std::chrono::duration<double, std::milli> tiempoMax = std::chrono::duration<double, std::milli>(tiempo);
    actual = std::chrono::system_clock::now();
    std::chrono::duration<double, std::nano> transcurrido = actual - previo;
    if (transcurrido > tiempoMax) return; // No duermo
    std::chrono::duration<double, std::milli> tiempoADormir = tiempoMax - transcurrido;
    std::this_thread::sleep_for(tiempoADormir);
}