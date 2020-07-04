#ifndef __CASCO_H__
#define __CASCO_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Casco : public Item, public PiezaDeDefensa{
    public:
    Casco(unsigned int defMax, unsigned int defMin, std::string unId);
    void utilizar(Personaje *personaje, unsigned int pos) override;
};
#endif
