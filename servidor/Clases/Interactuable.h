#ifndef __INTERACTUABLE_H__
#define __INTERACTUABLE_H__
#include "Posicion.h"
#include "Colisionable.h"
#include <string>
class Estado;
class Cliente;
class Item;
class Personaje;
class Interactuable : public Colisionable{
    protected:
    Posicion posicion;
    std::string id;
    float distanciaMaximaDeInteraccion;

    public:
    Interactuable(std::string id);
    virtual void interactuar(Estado *estado, Cliente *cliente) = 0;
    virtual void comprar(unsigned int pos, Estado *estado, Cliente *cliente) = 0;
    virtual void vender(unsigned int pos, Estado *estado, Cliente *cliente) = 0;
    virtual void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) = 0;
    virtual void vender(Item* item, Personaje *personaje, Cliente *cliente) = 0;
    virtual void listar(Personaje *personaje, Cliente *cliente) = 0;
    const quadtree::Box<float>& obtenerArea() const override;
    bool colisionaCon(const Colisionable &otro) const override;
    bool colisionaCon(const quadtree::Box<float> &area) const override;
    const Posicion& obtenerPosicion() const;
    const std::string obtenerId() const;
    virtual ~Interactuable();
};  

#endif
