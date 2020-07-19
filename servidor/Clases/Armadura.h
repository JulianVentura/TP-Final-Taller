#ifndef __ARMADURA_H__
#define __ARMADURA_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Armadura: public Item, public PiezaDeDefensa{
    public:
    Armadura(unsigned int defMax, 
             unsigned int defMin, 
             std::string unId,
             uint16_t idTCP,
             unsigned int unPrecio);
    /*
    Indica al personaje que debe equipar este arma situada en la posicion pos del inventario.
    */
    void utilizar(Personaje *personaje, unsigned int pos) override;
    /*
    Indica al personaje que debe desequipar esta armadura situada en la posicion pos del inventario.
    */
    void desequipar(Personaje *personaje, unsigned int pos) override;
    friend class Configuraciones;
};
#endif
