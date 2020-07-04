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
    std::string obtenerId();
    virtual void actualizarEstado(double tiempo, Mapa *mapa);

    virtual void atacar(Entidad *objetivo);
    virtual void recibirDanio(int danio, Entidad *atacante);
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void dropearItems();
    void consumirMana(unsigned int cantidad);
    void equipar(Arma *arma);
    void almacenar(std::unique_ptr<Item> item);
    friend class Configuraciones;
};

#endif
