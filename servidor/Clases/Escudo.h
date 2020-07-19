#ifndef __ESCUDO_H__
#define __ESCUDO_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Escudo : public Item, public PiezaDeDefensa{
    public:
    Escudo(unsigned int defMax, 
           unsigned int defMin, 
           std::string unId,
           uint16_t idTCP,
           unsigned int unPrecio);
    /*
    Indica al personaje que debe equipar este escudo situado en la posicion pos del inventario.
    */
    void utilizar(Personaje *personaje, unsigned int pos) override;
    /*
    Indica al personaje que debe desequipar este escudo situado en la posicion pos del inventario.
    */
    void desequipar(Personaje *personaje, unsigned int pos) override;
    friend class Configuraciones;
};
#endif