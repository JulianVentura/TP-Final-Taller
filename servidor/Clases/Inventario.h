#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__
#include <vector>
#include "Item.h"

class BolsaDeItems;
class Inventario{
    private:
    unsigned int limiteItems;
    std::vector<Item*> items;
    Item* item;
    Item* itemNulo;
    public:
    Inventario();
    Inventario(Inventario &otro) = delete;
    Inventario(Inventario &&otro) = delete;
    Inventario& operator=(Inventario &otro) = delete;
    Inventario& operator=(Inventario &&otro);
    int almacenar(Item* item);
    Item* obtenerItem(unsigned int pos);
    void eliminar(unsigned int pos);
    std::vector<Item*>* obtenerTodosLosItems();
    void eliminarTodosLosItems();
};


#endif
