#ifndef __COMERCIANTE_H__
#define __COMERCIANTE_H__

#include "Interactuable.h"
#include <vector>

class Personaje;
class Item;
class Comerciante : public Interactuable{
    private:
    std::vector<Item*> items;
    
    public:
    Comerciante(float x, float y);
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    ~Comerciante() override;
};

#endif