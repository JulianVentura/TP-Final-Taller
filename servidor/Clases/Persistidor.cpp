#include "Persistidor.h"

Persistidor::Persistidor(ColaSerializacion &cola, BaseDeDatos &base) : 
                                           colaSerializacion(cola),
                                           baseDeDatos(base){}

void Persistidor::procesar(){
    bool continuar = true;
    while (continuar){
        try{
            baseDeDatos.guardarCliente(std::move(colaSerializacion.pop()));
        }catch(...){
            //Cualquier excepcion o error que salte es motivo suficiente como para finalizar.
            //No me interesa reportar el error.
            continuar = false;
        }
    }
}

Persistidor::~Persistidor(){}