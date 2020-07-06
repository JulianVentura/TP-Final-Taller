#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Posicionable.h"
#include "Colisionable.h"
#include "Configuraciones.h"
#include "Arma.h"
#include "Inventario.h"
#include <string>

class Mapa;
class Entidad : public Colisionable, public Posicionable {
    protected:
    int vidaMaxima;
    int vidaActual;
    int manaMaximo;
    int manaActual;
    unsigned int fuerza;
    unsigned int inteligencia;
    unsigned int agilidad;
    unsigned int constitucion;
    unsigned int nivel;
    std::string id;
    Arma *arma;
    Inventario inventario;

    public:
    virtual ~Entidad();
    //Por ser colisionable
    Entidad(std::string id);
    virtual const quadtree::Box<float>& obtenerArea() const override;
    virtual bool colisionaCon(const Colisionable &otro) const override;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const override;
    //Por ser posicionable
    virtual const std::string obtenerId() const;
    virtual void actualizarEstado(double tiempo, Mapa *mapa);

    virtual void atacar(Entidad *objetivo);
    virtual void recibirDanio(int danio, Entidad *atacante);
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void dropearItems(Entidad *atacante);
    virtual void cobrar(unsigned int cantidad);
    void consumirMana(unsigned int cantidad);
    void equipar(Arma *arma);
    void almacenar(Item *item);
    friend class Configuraciones;
};

#endif
