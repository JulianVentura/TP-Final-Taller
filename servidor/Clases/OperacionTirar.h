#ifndef __OPERACION_TIRAR_H__
#define __OPERACION_TIRAR_H__
#include "Operacion.h"

class Cliente;
class OperacionTirar : public Operacion{
    private:
    Cliente *cliente;
    unsigned int pos;

    public:
    OperacionTirar(Cliente *cliente, unsigned int pos);
    ~OperacionTirar() override;
    /*
    Ejecuta la operacion de tirar, delegando en el personaje la accion de tirar un item del inventario
    almacenado en la posicion pos.
    */
    void ejecutar() override;
};

#endif
