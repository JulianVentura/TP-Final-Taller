#ifndef __PERSISTIDOR_H__
#define __PERSISTIDOR_H__

#include "../../common/Thread.h"
#include "ColaDeSerializacion.h"
#include "../../common/Serializacion.h"
#include "../../common/commonSocket.h"
#include "BaseDeDatos.h"

class Persistidor : public Thread{
    private:
    ColaSerializacion& colaSerializacion;
    BaseDeDatos &baseDeDatos;

    public:
    Persistidor(ColaSerializacion &cola, BaseDeDatos &base);
    Persistidor(Persistidor &otro) = delete;
    Persistidor(Persistidor &&otro) = delete;
    Persistidor& operator=(Persistidor &otro) = delete;
    Persistidor& operator=(Persistidor &&otro) = delete;
    /*
    Desencola de la cola de operaciones los datos de clientes serializados y delega en la
    BaseDeDatos para persistirlos.
    */
    void procesar();
    ~Persistidor();
};


#endif
