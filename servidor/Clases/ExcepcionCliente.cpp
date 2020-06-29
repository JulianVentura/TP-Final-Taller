#include "ExcepcionCliente.h"
#include <cstdio>
#include <cstdarg>

ExcepcionCliente::ExcepcionCliente(const char* formato, ...) : Excepcion(formato){
    va_list argumentos;
    va_start(argumentos, formato);
    
    vsnprintf(mensajeError, 
              TAM_MENSAJE_ERROR, 
              formato, 
              argumentos);
    va_end(argumentos);

    mensajeError[TAM_MENSAJE_ERROR-1] = 0;
}