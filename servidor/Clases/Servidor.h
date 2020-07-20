#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__
#include "OrganizadorSalas.h"
#include "Aceptador.h"
#include "Persistidor.h"
#include "ColaDeSerializacion.h"
#include "BaseDeDatos.h"

class Servidor{
    private:
    OrganizadorSalas organizadorSalas;
    BaseDeDatos baseDeDatos;
    Aceptador aceptador;
    Persistidor persistidor;
    ColaSerializacion colaSerializacion;
    public:
    //Luego se recibira un archivo de configuraciones desde donde se levantara el host, entre otras cosas.
    Servidor(const char* archivoConfig);
    Servidor(Servidor &&otro) = delete;
    Servidor(Servidor &otro) = delete;
    Servidor& operator=(Servidor &otro) = delete;
    Servidor& operator=(Servidor &&otro) = delete;
    /*
    Inicia la operacion del servidor.
    */
    void procesar();
};



#endif

