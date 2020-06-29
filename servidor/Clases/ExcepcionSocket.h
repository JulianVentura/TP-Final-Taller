#ifndef __EXCEPCION_SOCKET__
#define __EXCEPCION_SOCKET__
#include "Excepcion.h"

class ExcepcionSocket : public Excepcion{
    public:
    ExcepcionSocket(const char* formato, ...);
};

#endif
