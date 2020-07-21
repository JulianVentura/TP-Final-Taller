#ifndef __OPERACION_INTERACTUAR__
#define __OPERACION_INTERACTUAR__
#include "Operacion.h"

class Cliente;
class Mapa;
class OperacionInteractuar : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;
    unsigned int posItem;

    public:
    OperacionInteractuar(Cliente *cliente, Mapa *mapa, std::string idObjetivo);
    ~OperacionInteractuar() override;
    /*
    Ejecuta la operacion de interaccion, accediendo al mapa para obtener el objetivo e inicializando
    la cadena de compra, en la cual se determinara si la operacion es posible.
    */
    void ejecutar() override;
};


#endif