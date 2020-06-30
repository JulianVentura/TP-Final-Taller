#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Posicionable.h"
#include "Colisionable.h"
#include "Configuraciones.h"
#include "Arma.h"
#include <string>

class Mapa;
class Entidad : public Colisionable, public Posicionable {
    protected:
    unsigned int vidaMaxima;
    unsigned int vidaActual;
    unsigned int agilidad;
    unsigned int nivel;
    std::string id;
    Arma arma;

    public:
    virtual ~Entidad();
    //Por ser colisionable
    Entidad(unsigned int vidaMaxima, 
            unsigned int manaMaximo,
            unsigned int agilidad,
            unsigned int nivel,
            float x,
            float y, 
            std::string &id);
    virtual const quadtree::Box<float>& obtenerArea() const override;
    virtual bool colisionaCon(const Colisionable &otro) const override;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const override;
    //Por ser posicionable
    std::string obtenerId();
    virtual void actualizarEstado(double tiempo, Mapa *mapa);

    virtual void atacar(Entidad *objetivo);
    virtual void recibirDanio(unsigned int danio, Entidad *atacante);
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void dropearItems();
    friend class Configuraciones;
};

#endif
