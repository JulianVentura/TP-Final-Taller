#include "ExcepcionColaVacia.h"
#define MENSAJE_RETORNO "Cola cerrada\n"


ExcepcionColaVacia::ExcepcionColaVacia() noexcept{}
const char *ExcepcionColaVacia::what() const noexcept{
    return MENSAJE_RETORNO;
}
ExcepcionColaVacia::~ExcepcionColaVacia() noexcept{}
