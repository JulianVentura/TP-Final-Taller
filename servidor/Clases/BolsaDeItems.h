#ifndef __BOLSA_DE_ITEMS_H__
#define __BOLSA_DE_ITEMS_H__
#include "Interactuable.h"
#include <vector>
#include <atomic>
class Personaje;
class Item;
class BolsaDeItems : public Interactuable{
    private:
    static unsigned int contadorInstancias;
    std::vector<Item*> items;
    unsigned int elementos;
    std::atomic<bool> bolsaVacia;
    public:
    BolsaDeItems(Posicion posicion, std::vector<Item*> items);
    BolsaDeItems(Posicion posicion, Item *item);
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    bool estaVacia();
    ~BolsaDeItems() override;
};

#endif