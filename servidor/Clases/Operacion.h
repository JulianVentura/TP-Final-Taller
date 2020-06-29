#ifndef __OPERACION__
#define __OPERACION__
#include <string>

class Operacion{
    public:
    virtual ~Operacion() = 0;
    virtual void ejecutar() = 0;
};

#endif
