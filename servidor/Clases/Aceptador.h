#ifndef __ACEPTADOR_H__
#define __ACEPTADOR_H__
#include "Thread.h"
#include "BaseDeDatos.h"
#include "OrganizadorSalas.h"
#include <atomic>
class Aceptador : public Thread{
    private:
    //Socket servidor;
    //OrganizadorClientes clientes;
    std::atomic<bool> continuar;
    /*
    Se encarga de recuperar y liberar los clientes que ya han finalizado 
    su operacion, haciendo el join de los threads correspondientes y 
    eliminandolos de la lista de clientes.
    */
    void recuperarFinalizados();
    /*
    Se encarga de recuperar a todos los clientes de la lista de clientes.
    Si el cliente no ha finalizado su operacion lo esperara y luego realizara
    el correspondiente join al thread que lo conduce.
    No eliminara a los clientes de la lista de clientes, esto se hace
    automaticamente en el destructor de esta clase.
    */
    void recuperarTodosLosClientes();
    
    public:
    /*
    Crea un servidor en host y puerto que se encargara de aceptar
    conexiones entrantes.
    En caso de error lanza una instancia de Excepcion.
    */
    Aceptador(const char* host, 
              OrganizadorSalas &organizadorSalas, 
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