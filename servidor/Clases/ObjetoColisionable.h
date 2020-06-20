#ifndef __OBJETO_COLISIONABLE_H__
#define __OBJETO_COLISIONABLE_H__
#include "Colisionable.h"
#include "Box.h"
class ObjetoColisionable : public Colisionable{
    private:
    quadtree::Box<float> areaQueOcupa;
    public:
    ObjetoColisionable(quadtree::Box<float> &&rectangulo);
    ObjetoColisionable(ObjetoColisionable &&otro);
    virtual ~ObjetoColisionable();
    const quadtree::Box<float>& obtenerArea() const override;
    bool colisionaCon(const Colisionable &otro) const override;
    bool colisionaCon(const quadtree::Box<float> &otroArea) const override;
};

#endif
