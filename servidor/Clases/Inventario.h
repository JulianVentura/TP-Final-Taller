#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__
#include <memory>
#include <vector>
#include "Item.h"

class Inventario{
    private:
    unsigned int limiteItems;
    std::vector<std::unique_ptr<Item>> items;
    
    public:
    Inventario();
    void almacenar(std::unique_ptr<Item> item);
    Item* obtenerItem(unsigned int pos);
    void eliminar(unsigned int pos);
    std::vector<std::string> obtenerTodosLosItems();

};


#endif
