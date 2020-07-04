#ifndef __BOLSA_DE_ITEMS_H__
#define __BOLSA_DE_ITEMS_H__
#include "Item.h"
#include "Posicion.h"
#include <list>
#include <memory>
class BolsaDeItems{
    private:
    Posicion posicion;
    //std::list<std::unique_ptr<Item>> items;

    public:
    BolsaDeItems();
};

#endif
