#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Posicionable.h"
#include "Colisionable.h"
#include <string>

class Entidad : public Colisionable, public Posicionable{
    protected:
    unsigned int vidaMaxima;
    unsigned int manaMaximo;
    unsigned int vidaActual;
    unsigned int manaActual;
    std::string id;

    public:
    virtual ~Entidad();
    //Por ser colisionable
    Entidad(unsigned int vidaMaxima, unsigned int manaMaximo, const char* id);
    virtual Rectangulo& obtenerArea() override;
    virtual bool colisionaCon(Colisionable &otro) override;
    virtual bool colisionaCon(Rectangulo &area) override;
    //Por ser posicionable
    virtual Posicion&& avanzar() override;
    std::string obtenerId();
};

#endif
