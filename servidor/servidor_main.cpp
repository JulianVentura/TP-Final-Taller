#include "Clases/Servidor.h"
#include <iostream>
//Valores de retorno
#define EXITO 0
#define ERROR -1
//Validacion de parametros
#define NUMERO_PARAMETROS 2
#define POSICION_PUERTO 1

int inicializarServidor(const char *puerto){
    try{
        Servidor servidor(puerto);
        servidor.procesar();
    }catch(const std::exception &e){
        std::cerr << e.what() <<std::endl;
        return ERROR;
    }catch(...){
        std::cerr << "Error desconocido capturado en pruebaServidor" <<std::endl;
        return ERROR;
    }
    return EXITO;
}

int main(int argc, const char* argv[]){
    if (argc != NUMERO_PARAMETROS){
        std::cerr << "Error en la cantidad de parametros" << std::endl;
        return ERROR;
    }
    return inicializarServidor(argv[POSICION_PUERTO]);
}
