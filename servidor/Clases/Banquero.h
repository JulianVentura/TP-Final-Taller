#ifndef __BANQUERO_H__
#define __BANQUERO_H__

#include "Interactuable.h"
#include <vector>
class Personaje;
class Item;
class Banquero : public Interactuable{
    public:
    Banquero(float x, float y);
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    ~Banquero() override;
};

#endif
