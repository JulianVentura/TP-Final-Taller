#ifndef __ACEPTADOR_H__
#define __ACEPTADOR_H__

#include <atomic>
#include <sys/socket.h> // Para SHUT_RDWR

#include "../../common/commonSocket.h"
#include "../../common/Thread.h"

#include "BaseDeDatos.h"
#include "OrganizadorSalas.h"
#include "OrganizadorClientes.h"

class Aceptador : public Thread{
    private:
    Socket servidor;
    OrganizadorClientes organizadorClientes;
    OrganizadorSalas &organizadorSalas;
    BaseDeDatos &baseDeDatos;
    std::atomic<bool> continuar;

    public:
    /*
    Crea un servidor en host y puerto que se encargara de aceptar
    conexiones entrantes.
    En caso de error lanza una instancia de Excepcion.
    */
    Aceptador(OrganizadorSalas &organizadorSalas, 
              BaseDeDatos &baseDeDatos);
    Aceptador(Aceptador &&otro) = delete;
    Aceptador(Aceptador &otro) = delete;
    Aceptador& operator=(Aceptador &&otro) = delete;
    Aceptador& operator=(Aceptador &otro) = delete;
    /*
    Aceptara conexiones entrantes, las procesara en un esquema concurrente
    y finalizara, liberando los recursos y cerrando las conexiones, cuando
    se invoque al metodo finalizar() o se encuentre un error.
    */
    virtual void procesar() override;
    /*
    Finaliza la ejecucion del servidor, impidiendo a nuevos clientes
    conectarse.
    */
    void finalizar();
};

#endif