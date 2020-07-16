#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include "../../common/Serializacion.h"
class Personaje;
class Item{
    protected:
    std::string id;
    uint16_t idTCP;
    unsigned int precio;
    public:
    Item(std::string id, uint16_t idTCP, unsigned int unPrecio);
    virtual ~Item();
    std::string obtenerId();
    unsigned int obtenerPrecio();
    const uint16_t obtenerIDTCP() const;
    virtual void utilizar(Personaje *personaje, unsigned int pos) = 0;
    virtual void desequipar(Personaje *personaje, unsigned int pos) = 0;
    const SerializacionItem serializar() const;
};

#endif
