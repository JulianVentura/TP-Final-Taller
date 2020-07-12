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
    void ejecutar() override;
};


#endif