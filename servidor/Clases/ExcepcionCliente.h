#ifndef __EXCEPCION_CLIENTE_H__
#define __EXCEPCION_CLIENTE_H__
#include "Excepcion.h"

class ExcepcionCliente : public Excepcion{
    public:
    ExcepcionCliente(const char* formato, ...);
};


#endif
