#ifndef __EXCEPCION_COLA_VACIA__
#define __EXCEPCION_COLA_VACIA__

#include <typeinfo>


class ExcepcionColaVacia : public std::exception{
    public:
    ExcepcionColaVacia() noexcept;
    virtual const char *what() const noexcept;
    virtual ~ExcepcionColaVacia() noexcept;
};

#endif
