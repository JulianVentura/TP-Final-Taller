#include "Aceptador.h"

#include <iostream>
#include <utility> //Para std::move
#include <thread>

#include "ExcepcionSocket.h"
#include "ExcepcionCliente.h"
#include "Divulgador.h"


//////////////////Metodos publicos///////////////////////////////

Aceptador::Aceptador(OrganizadorSalas &unOrganizadorSalas, 
                     BaseDeDatos &unaBaseDeDatos) : 
                     organizadorSalas(unOrganizadorSalas),
                     baseDeDatos(unaBaseDeDatos),
                     continuar(true){
    Divulgador::inicializarInstancia(&organizadorClientes);
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //El socket defaultea a "localhost", para la entrega final eso se va
    //a poder elegir del configuraciones.json
    //std::string host = config->obtenerAceptadorHost();
    std::string puerto = config->obtenerAceptadorPuerto();
    unsigned int numConexionesEnEspera = config->
    obtenerAceptadorNumConexionesEnEspera();
    servidor.ligar( puerto.c_str());
    servidor.escuchar(numConexionesEnEspera);
}


void Aceptador::procesar(){
    while (continuar){
        try{
            Socket socketCliente = servidor.aceptar();
            organizadorClientes.recuperarFinalizados();
            std::unique_ptr<Cliente> cliente(new Cliente(std::move(socketCliente),
                                                         organizadorSalas,
                                                         organizadorClientes,
                                                         baseDeDatos));
            cliente.get()->comenzar();
            organizadorClientes.incorporarCliente(std::move(cliente));
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
    servidor.cerrar_canal(SHUT_RDWR);
    try{
        Divulgador *divulgador = Divulgador::obtenerInstancia();
        divulgador->finalizar();
        divulgador->recuperar();
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
    servidor.cerrar_canal(SHUT_RDWR);
}