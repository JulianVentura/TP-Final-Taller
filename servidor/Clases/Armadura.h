#ifndef __ARMADURA_H__
#define __ARMADURA_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Armadura: public Item, public PiezaDeDefensa{
    public:
    Armadura(unsigned int defMax, unsigned int defMin, std::string unId);
    void utilizar(Personaje *personaje, unsigned int pos) override;
};
#endif