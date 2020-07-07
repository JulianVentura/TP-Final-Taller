#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
class Personaje;
class Item{
    protected:
    std::string id;
    unsigned int precio;
    public:
    Item(std::string id, unsigned int unPrecio);
    virtual ~Item();
    std::string obtenerId();
    unsigned int obtenerPrecio();
    virtual void utilizar(Personaje *personaje, unsigned int pos) = 0;
};

#endif
