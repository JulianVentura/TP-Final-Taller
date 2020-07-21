#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__
#include <vector>
#include "../../common/Serializacion.h"
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
    /*
    Almacena un item al inventario, si no hay lugar disponible se lanza una Excepcion.
    */
    int almacenar(Item* item);
    /*
    Devuelve un item del inventario, especificado en la posicion pos. 
    Si no hay lugar disponible se lanza una Excepcion.
    */
    Item* obtenerItem(unsigned int pos);
    /*
    Elimina el item del inventario en la posicion pos.
    */
    void eliminar(unsigned int pos);
    /*
    Devuelve un puntero a un vector de items que contiene los almacenados del inventario.
    */
    std::vector<Item*>* obtenerTodosLosItems();
    /*
    Vacia todo los items del inventario, dejandolo vacio
    */
    void eliminarTodosLosItems();
    void serializar(SerializacionItem *ser);
};


#endif
