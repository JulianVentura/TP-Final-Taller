#ifndef __OPERACION_ENCAPSULADA_H__
#define __OPERACION_ENCAPSULADA_H__
#include "Operacion.h"
#include "Excepcion.h"
class OperacionEncapsulada{

    private:
    Operacion *operacion;
    bool punteroValido;
    public:
    OperacionEncapsulada();
    OperacionEncapsulada(Operacion *operacion);
    OperacionEncapsulada(OperacionEncapsulada &otro) = delete;
    OperacionEncapsulada(OperacionEncapsulada &&otro);
    OperacionEncapsulada& operator=(OperacionEncapsulada &otro) = delete;
    OperacionEncapsulada& operator=(OperacionEncapsulada &&otro);
    ~OperacionEncapsulada();
    /*
    Devuelve el puntero a operacion.
    */
    Operacion* obtenerOperacion();

};


#endif