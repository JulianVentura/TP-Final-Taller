#ifndef __ESCUDO_H__
#define __ESCUDO_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Escudo : public Item, public PiezaDeDefensa{
    public:
    Escudo(unsigned int defMax, unsigned int defMin, std::string unId);
    void utilizar(Personaje *personaje, unsigned int pos) override;
};
#endif