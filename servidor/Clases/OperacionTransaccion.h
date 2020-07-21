#ifndef __OPERACION_TRANSACCION__
#define __OPERACION_TRANSACCION__
#include "Operacion.h"

class Cliente;
class Mapa;
class OperacionTransaccion : public Operacion{
    private:
    Cliente *cliente;
    Mapa *mapa;
    std::string idObjetivo;
    bool esDeposito;

    public:
    OperacionTransaccion(Cliente *cliente, Mapa *mapa, std::string idObjetivo, bool esDeposito);
    ~OperacionTransaccion() override;
    /*
    Ejecuta la operacion de transaccion, accediendo al mapa para buscar al objetivo.
    Lanza la cadena de llamados para realizar la transaccion, delegando en el objetivo.
    */
    void ejecutar() override;
};


#endif