#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Posicionable.h"
#include "Colisionable.h"
#include <string>

class Entidad : public Colisionable, public Posicionable {
    protected:
    unsigned int vidaMaxima;
    unsigned int manaMaximo;
    unsigned int vidaActual;
    unsigned int manaActual;
    std::string id;

    public:
    virtual ~Entidad();
    //Por ser colisionable
    Entidad(unsigned int vidaMaxima, unsigned int manaMaximo, std::string &id);
    virtual const quadtree::Box<float>& obtenerArea() const override;
    virtual bool colisionaCon(const Colisionable &otro) const override;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const override;
    //Por ser posicionable
    virtual Posicion&& avanzar() override;
    std::string obtenerId();
    void actualizarEstado(double tiempo);
};

#endif
