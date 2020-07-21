#ifndef __OPERACION_MOVER__
#define __OPERACION_MOVER__
#include "Operacion.h"
#include "Personaje.h"
typedef enum DIR_MOVIMIENTO {MOVER_ARRIBA, 
                             MOVER_ABAJO, 
                             MOVER_DERECHA, 
                             MOVER_IZQUIERDA,
                             FINALIZAR_MOVIMIENTO} DireccionMovimiento;

class OperacionMover : public Operacion{
    private:
    Personaje *personaje;
    DireccionMovimiento direccion;
    
    public:
    OperacionMover(Personaje *personaje, DireccionMovimiento direccion);
    ~OperacionMover() override;
    /*
    Ejecuta la operacion de mover, delegando en el Personaje la accion de mover.
    */
    void ejecutar() override;
};


#endif
