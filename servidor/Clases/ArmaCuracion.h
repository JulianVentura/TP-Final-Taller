#ifndef __ARMA_CURACION_H__
#define __ARMA_CURACION_H__
#include "Arma.h"


class ArmaCuracion : public Arma{
    public:
    ArmaCuracion(int curMax, 
                 int curMin, 
                 unsigned int consMana, 
                 float radioAtaque,
                 double tiempoAtaque, 
                 std::string id,
                 std::string idProyectil,
                 uint16_t idTCP,
                 unsigned int unPrecio);
    ArmaCuracion(ArmaCuracion &otro) = delete;
    ArmaCuracion(ArmaCuracion &&otro) = delete;
    ArmaCuracion& operator=(ArmaCuracion &otro) = delete;
    ArmaCuracion& operator=(ArmaCuracion &&otro) = delete;
    /*
    Efectua el ataque de curacion al objetivo y devuelve un mensaje con el resultado obtenido.
    El ataque no se realiza si el mana del lanzador es inferior al necesario por el arma o si
    la distancia entre el lanzador y objetivo es mayor al rango del arma. En ambos casos se devuelve
    un mensaje descriptivo.
    Una vez efectuado el ataque se creara una instancia de Proyectil que sera cargada en el mapa.
    El arma permite realizar ataques sobre uno mismo, que tendran como consecuencia la curacion del lanzador.
    */
    std::string atacar(Entidad *objetivo, Entidad *lanzador, Mapa *mapa) override;
    friend class Configuraciones;
};


#endif