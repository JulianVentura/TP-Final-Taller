#ifndef __OPERACION_VENDER_H__
#define __OPERACION_VENDER_H__
#include "Operacion.h"

class Cliente;
class Mapa;
class OperacionVender : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;
    unsigned int posItem;

    public:
    OperacionVender(Cliente *cliente, Mapa *mapa, unsigned int pos, std::string idObjetivo);
    ~OperacionVender() override;
    void ejecutar() override;
};


#endif