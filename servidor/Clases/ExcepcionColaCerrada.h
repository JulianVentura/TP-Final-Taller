#ifndef __EXCEPCION_COLA_CERRADA__
#define __EXCEPCION_COLA_CERRADA__

#include <typeinfo>


class ExcepcionColaCerrada : public std::exception{
    public:
    ExcepcionColaCerrada() noexcept;
    virtual const char *what() const noexcept;
    virtual ~ExcepcionColaCerrada() noexcept;
};

#endif
