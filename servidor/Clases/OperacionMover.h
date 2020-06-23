#ifndef __OPERACION_MOVER__
#define __OPERACION_MOVER__
#include "Operacion.h"
#include "Personaje.h"
typedef enum MOVIMIENTO {MOVER_ARRIBA, 
                         MOVER_ABAJO, 
                         MOVER_DERECHA, 
                         MOVER_IZQUIERDA} DireccionMovimiento;

class OperacionMover : public Operacion{
    private:
    Personaje *personaje;
    DireccionMovimiento direccion;
    
    public:
    OperacionMover(Personaje *personaje, DireccionMovimiento direccion);
    ~OperacionMover() override;
    void ejecutar() override;
};


#endif