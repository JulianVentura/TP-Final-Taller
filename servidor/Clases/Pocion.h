#ifndef __POCION_H__
#define __POCION_H__
#include "Item.h"
class Personaje;
class Pocion : public Item{
    private:
    unsigned int curacionVida;
    unsigned int curacionMana;

    public:
    Pocion(unsigned int curacionVida, 
           unsigned int curacionMana, 
           std::string unId,
           uint16_t idTCP,
           unsigned int unPrecio);
    void utilizar(Personaje *personaje, unsigned int pos) override;
    void desequipar(Personaje *personaje) override;
};


#endif
