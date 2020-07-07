#include "Excepcion.h"
#include <cstdio>
#include <cstdarg>

Excepcion::Excepcion(const char* formato, ...) noexcept : mensajeError{0}{
    va_list argumentos;
    va_start(argumentos, formato);
    
    vsnprintf(mensajeError, 
              TAM_MENSAJE_ERROR, 
              formato, 
              argumentos);
    va_end(argumentos);

    mensajeError[TAM_MENSAJE_ERROR-1] = 0;
}

const char* Excepcion::what() const noexcept{
    return mensajeError;
}

Excepcion::~Excepcion(){
    //Do nothing
}
