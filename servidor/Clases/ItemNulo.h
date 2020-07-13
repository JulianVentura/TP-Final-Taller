#ifndef __ITEM_NULO_H__
#define __ITEM_NULO_H__

#include <string>

#include "Item.h"
#include "Personaje.h"

class ItemNulo : public Item{
public:
    ItemNulo(std::string id, uint16_t idTCP, unsigned int unPrecio);
    void utilizar(Personaje *personaje, unsigned int pos);
    void desequipar(Personaje *personaje, unsigned int pos);
    ~ItemNulo();
};

#endif /*__ITEM_NULO_H__*/