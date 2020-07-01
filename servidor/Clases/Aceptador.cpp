#include "Aceptador.h"
#include <iostream>
#include <utility> //Para std::move
#include "ExcepcionSocket.h"
#include "ExcepcionCliente.h"
#include <thread>

#define NUMERO_DE_CONEXIONES_EN_ESPERA 10

//////////////////Metodos publicos///////////////////////////////

Aceptador::Aceptador(const char* host,
                     const char* puerto,
                     OrganizadorSalas &unOrganizadorSalas, 
                     BaseDeDatos &unaBaseDeDatos) : 
                     organizadorSalas(unOrganizadorSalas),
                     baseDeDatos(unaBaseDeDatos),
                     divulgador(organizadorClientes),
                     continuar(true){
    servidor.bindYSetearOpciones(host, puerto);
    servidor.escuchar(NUMERO_DE_CONEXIONES_EN_ESPERA);
    divulgador.comenzar();
}


void Aceptador::procesar(){
    while (continuar){
        try{
            Socket socketCliente = servidor.aceptar();
            organizadorClientes.recuperarFinalizados();
            std::unique_ptr<Cliente> cliente(new Cliente(std::move(socketCliente),
                                                         organizadorSalas,
                                                         organizadorClientes,
                                                         baseDeDatos,
                                                         divulgador));
            cliente.get()->comenzar();
            organizadorClientes.incorporarCliente(std::move(cliente));
        }catch(const ExcepcionSocket &e){
            //No me aporta nada imprimir un error de socket
        }catch(const ExcepcionCliente &e){
            //No me aporta nada imprimir este error.
        }catch(const std::exception &e){
            std::cerr << e.what() << std::endl;
        }catch(...){
            std::cerr << "Error desconocido encontrado dentro del "
                     "metodo procesar de la clase Aceptador" << std::endl;
        }      
    }    
    //Esto en realidad no es necesario, pero mejor setearlo a false
    //para que sea consistente.
    continuar = false;
    servidor.apagar(READ_AND_WRITE);
    try{
        divulgador.finalizar();
        divulgador.recuperar();
        organizadorClientes.recuperarTodosLosClientes();
    }catch(...){
        std::cerr << "Error al intentar recuperar a los "
        "clientes en la clase Aceptador" << std::endl;
    }
}

void Aceptador::finalizar(){
    continuar = false;
    /*
    Los sockets de C permiten realizar un shutdown y cierre
    sin entrar en una RC, por lo tanto esta operacion es segura.
    */
    servidor.apagar(READ_AND_WRITE);
}