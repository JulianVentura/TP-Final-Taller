#ifndef __OPERACION_COMPRAR_H__
#define __OPERACION_COMPRAR_H__
#include "Operacion.h"

class Cliente;
class Mapa;
class OperacionComprar : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;
    unsigned int posItem;

    public:
    OperacionComprar(Cliente *cliente, Mapa *mapa, unsigned int pos, std::string idObjetivo);
    ~OperacionComprar() override;
    void ejecutar() override;
};


#endif