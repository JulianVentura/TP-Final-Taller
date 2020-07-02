#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
class Personaje;
class Item{
    protected:
    std::string id;
    public:
    Item();
    virtual ~Item();
    std::string obtenerId();
    virtual void utilizar(Personaje *personaje, unsigned int pos) = 0;

};

#endif
