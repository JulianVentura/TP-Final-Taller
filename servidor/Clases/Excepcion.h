#ifndef __EXCEPCION__
#define __EXCEPCION__
#include <typeinfo>
#define TAM_MENSAJE_ERROR 256

class Excepcion : public std::exception{
    protected:
    char mensajeError[TAM_MENSAJE_ERROR];

    public:
    Excepcion(const char* formato, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~Excepcion() noexcept;
};

#endif
