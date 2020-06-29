#include "ExcepcionSocket.h"
#include <cstdio>
#include <cstdarg>
#include <errno.h>
#include <cstring>
#include <cerrno>

ExcepcionSocket::ExcepcionSocket(const char* formato, ...) : 
                                 Excepcion(formato){
    //Es buena idea copiar errno para evitar que se sobrescriba
    int copiaErrno = errno;
    //Comienzo la lista de argumentos variable
    va_list argumentos;
    va_start(argumentos, formato);
    
    int escrito = vsnprintf(mensajeError, 
                            TAM_MENSAJE_ERROR, 
                            formato, 
                            argumentos);
                            
    va_end(argumentos);
    //Copio el mensaje de error interpretado con strerror dentro del mensaje
    
    strncpy(mensajeError + escrito,
            strerror(copiaErrno),
            TAM_MENSAJE_ERROR - escrito);
    
    //Cierro el mensaje con un fin de cadena.
    mensajeError[TAM_MENSAJE_ERROR - 1] = 0;
}
