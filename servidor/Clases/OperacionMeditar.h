#ifndef __OPERACION_MEDITAR_H__
#define __OPERACION_MEDITAR_H__
#include "Operacion.h"

class Cliente;
class OperacionMeditar : public Operacion{
    private:
    Cliente *cliente;

    public:
    OperacionMeditar(Cliente *cliente);
    ~OperacionMeditar() override;
    /*
    Ejecuta la operacion de meditacion, delegando en el Personaje la accion de meditar.
    */
    void ejecutar() override;
};


#endif