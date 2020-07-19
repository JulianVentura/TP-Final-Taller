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
    void procesar();
    ~Persistidor();
};


#endif
