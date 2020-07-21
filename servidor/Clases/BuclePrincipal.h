#ifndef __BUCLE_PRINCIPAL_H__
#define __BUCLE_PRINCIPAL_H__
#include "../../common/Thread.h"
#include "Mapa.h"
#include "ColaOperaciones.h"
#include "Reloj.h"
#include <atomic>
#include <map>


class Sala;
class Cliente;
class BuclePrincipal : public Thread{
    private:
    unsigned int msPorActualizacion;
    unsigned int msDescanso;
    ColaOperaciones &colaDeOperaciones;
    Mapa &mapa;
    std::atomic<bool> continuar;
    Reloj reloj;
    Sala &miSala;
    /*
    Desencola las operaciones de la cola de operaciones pasada por parametro y las ejecuta.
    */
    void procesarOperaciones();
    public:
    BuclePrincipal(ColaOperaciones &cola, Mapa &unMapa, Sala &unaSala);
    BuclePrincipal(BuclePrincipal &otro) = delete;
    BuclePrincipal(BuclePrincipal &&otro) = delete;
    BuclePrincipal& operator=(BuclePrincipal &otro) = delete;
    BuclePrincipal& operator=(BuclePrincipal &&otro) = delete;
    virtual ~BuclePrincipal();
    /*
    Procesa el mismo bucle principal, manteniendo un frame-rate constante y ordenando a 
    sala y mapa la actualizacion de clientes y entidades.
    */
    void procesar() override;
    void finalizar();
};

#endif 
