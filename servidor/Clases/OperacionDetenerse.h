#ifndef __OPERACION_DETENERSE__
#define __OPERACION_DETENERSE__
#include "Operacion.h"
#include "Personaje.h"


class OperacionDetenerse : public Operacion{
    private:
    Personaje *personaje;
    
    public:
    OperacionDetenerse(Personaje *personaje);
    ~OperacionDetenerse() override;
    void ejecutar() override;
};


#endif