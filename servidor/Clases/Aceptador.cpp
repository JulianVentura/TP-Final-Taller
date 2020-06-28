#include "Aceptador.h"
#include <iostream>
#include <list>
#include <utility> //Para std::move

#define NUMERO_DE_CONEXIONES_EN_ESPERA 10

///////////////////Metodos privados/////////////////////////////

void Aceptador::recuperarFinalizados(){
    //De esto se encarga el organizador de clientes
    /*
    std::list<ClienteEncapsulado>::iterator it = clientes.begin();
    while (it != clientes.end()){
        if ((*it).cliente()->haFinalizado()){
            (*it).cliente()->recuperar();
            it = clientes.erase(it);
        }else{
            ++it;
        }
    }
    */
}

void Aceptador::recuperarTodosLosClientes(){
    /*
    try{
        std::list<ClienteEncapsulado>::iterator it = clientes.begin();
        while (it != clientes.end()){
            (*it).cliente()->recuperar();
            ++it;
        }
    }catch(...){
        //Solo catcheo elipsis para no perjudicar legibilidad.
        std::cerr << "Error al recuperar todos los clientes en Aceptador. "
                     "Se esperara a que los clientes finalicen."
                  << std::endl;
    }
    */
}

//////////////////Metodos publicos///////////////////////////////

Aceptador::Aceptador(const char* host, 
                     OrganizadorSalas &organizadorSalas, 
                     BaseDeDatos &baseDeDatos) : 
                     continuar(true){
    //servidor.bindYSetearOpciones(host, puerto);
    //servidor.escuchar(NUMERO_DE_CONEXIONES_EN_ESPERA);
}


void Aceptador::procesar(){
    /*
    try{
        while (continuar){
            Socket socketCliente = servidor.aceptar();
            ClienteEncapsulado cliente(std::move(socketCliente));
            cliente.cliente()->comenzar();
            clientes.push_back(std::move(cliente));
            recuperarFinalizados();
        }
    }catch(const ExcepcionSocket &e){
        //Considero que esto no es un error, no quiero imprimirlo.
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }catch(...){
        std::cerr << "Error desconocido encontrado dentro del "
                     "metodo procesar de la clase Aceptador" << std::endl;
    }
    //Esto en realidad no es necesario, pero mejor setearlo a false
    //para que sea consistente.
    continuar = false;
    servidor.apagar(READ_AND_WRITE);
    recuperarTodosLosClientes();
    */
}

void Aceptador::finalizar(){
    continuar = false;
    /*
    Los sockets de C permiten realizar un shutdown y cierre
    sin entrar en una RC, por lo tanto esta operacion es segura.
    */
    //servidor.apagar(READ_AND_WRITE);
}