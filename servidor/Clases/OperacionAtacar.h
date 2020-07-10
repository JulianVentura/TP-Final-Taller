#ifndef __OPERACION_ATACAR_H__
#define __OPERACION_ATACAR_H__
#include "Operacion.h"

class Divulgador;
class Mapa;
class Cliente;
class OperacionAtacar : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;

    public:
    OperacionAtacar(Cliente *cliente, Mapa *mapa, std::string idObjetivo);
    ~OperacionAtacar() override;
    void ejecutar() override;
};


#endif