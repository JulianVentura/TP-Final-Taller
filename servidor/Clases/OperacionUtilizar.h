#ifndef __OPERACION_UTILIZAR_H__
#define __OPERACION_UTILIZAR_H__
#include "Operacion.h"

class Cliente;
class OperacionUtilizar : public Operacion{
    private:
    Cliente *cliente;
    uint16_t pos;

    public:
    OperacionUtilizar(Cliente *cliente, uint16_t pos);
    ~OperacionUtilizar() override;
    /*
    Ejecuta la operacion de utilizacion, delegando en el personaje.
    Se utilizara el item almacenado en el inventario en la posicion pos.
    */
    void ejecutar() override;
};

#endif