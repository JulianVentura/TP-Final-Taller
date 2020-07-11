#ifndef __CASCO_H__
#define __CASCO_H__
#include "Item.h"
#include "PiezaDeDefensa.h"

class Personaje;
class Casco : public Item, public PiezaDeDefensa{
    public:
    Casco(unsigned int defMax, 
          unsigned int defMin, 
          std::string unId,
          uint16_t idTCP,
          unsigned int unPrecio);
    void utilizar(Personaje *personaje, unsigned int pos) override;
    void desequipar(Personaje *personaje, unsigned int pos) override;
    friend class Configuraciones;
};
#endif
