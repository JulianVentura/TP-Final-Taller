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
    std::string atacar(Entidad *objetivo, Entidad *lanzador, Mapa *mapa) override;
    friend class Configuraciones;
};


#endif