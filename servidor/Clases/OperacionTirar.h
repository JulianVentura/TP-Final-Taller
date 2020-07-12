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
    void ejecutar() override;
};

#endif
