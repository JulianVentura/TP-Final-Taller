#ifndef __OBJETO_COLISIONABLE_H__
#define __OBJETO_COLISIONABLE_H__
#include "Colisionable.h"
class ObjetoColisionable : public Colisionable{
    private:
    Rectangulo areaQueOcupa;
    public:
    ObjetoColisionable(Rectangulo &&rectangulo);
    ObjetoColisionable(ObjetoColisionable &&otro);
    virtual ~ObjetoColisionable();
    Rectangulo& obtenerArea() override;
    bool colisionaCon(Colisionable &otro) override;
    bool colisionaCon(Rectangulo &otroArea) override;
};

#endif
