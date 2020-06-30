#ifndef __ARMA_H__
#define __ARMA_H__
#include "Configuraciones.h"
class Entidad;
class Arma{
    private:
    unsigned int danioMax;
    unsigned int danioMin;
    float radioAtaque;
    
    public:
    Arma(unsigned int danioMax, unsigned int danioMin, float radioAtaque);
    Arma(Arma &otro) = delete;
    Arma(Arma &&otro) = delete;
    Arma& operator=(Arma &otro) = delete;
    Arma& operator=(Arma &&otro) = delete;
    void atacar(Entidad *objetivo, Entidad *atacante);
    friend class Configuraciones;
};


#endif
