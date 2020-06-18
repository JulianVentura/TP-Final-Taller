#include "ExcepcionColaCerrada.h"
#define MENSAJE_RETORNO "Cola cerrada\n"


ExcepcionColaCerrada::ExcepcionColaCerrada() noexcept{}
const char *ExcepcionColaCerrada::what() const noexcept{
    return MENSAJE_RETORNO;
}
ExcepcionColaCerrada::~ExcepcionColaCerrada() noexcept{}
