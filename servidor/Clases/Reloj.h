#ifndef __RELOJ_H__
#define __RELOJ_H__
#include <chrono>

class Reloj{
    private:
    std::chrono::high_resolution_clock::time_point previo;
    std::chrono::high_resolution_clock::time_point actual;
    double periodo;

    public:
    Reloj();
    Reloj(Reloj &&otro) = delete;
    Reloj(Reloj &otro) = delete;
    Reloj& operator=(Reloj &&otro) = delete;
    Reloj& operator=(Reloj &otro) = delete;
    /*
    Devuelve el tiempo transcurrido entre el tick previo y el momento
    de llamada actual
    */
    double tiempoTranscurrido();
    /*
    Devuelve el tiempo transcurrido entre el tick previo y el momento
    de llamada actual, ademas de actualizar el tick previo y actual.
    */
    double actualizar();

    void dormir(double tiempo);

};

#endif
