#include "Inventario.h"
#include "BolsaDeItems.h"
#include "Excepcion.h"
#include "FabricaDeItems.h"
//Esto deberia sincronizarse con el cliente, un define en un common.
#define LIMITE_INVENTARIO 18
//Ver si es necesario levantar el limite de items del archivo de configuraciones

Inventario::Inventario() : limiteItems(LIMITE_INVENTARIO){
    //Provisorio
    items.clear();
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    itemNulo = fabricaItems -> crearItemNulo();
    for(int i = 0;i < LIMITE_INVENTARIO;i++){
        items.push_back(itemNulo);
    }
}


Inventario& Inventario::operator=(Inventario &&otro){
    this->items = std::move(otro.items);
    this->limiteItems = std::move(otro.limiteItems);
    return *this;
}

int Inventario::almacenar(Item* item){
    bool almacenado = false;
    std::size_t i = 0;
    for (i = 0; i < items.size(); i++){
        if (items[i] == itemNulo){
            items[i] = std::move(item);
            almacenado = true;
            break;
        }
    }
    if (!almacenado){
        throw Excepcion
        ("Error: Se ha intentado almacenar un nuevo item, pero el inventario esta lleno.");
    }
    return i;
}

Item* Inventario::obtenerItem(unsigned int pos){
    if (pos >= LIMITE_INVENTARIO || !items[pos]){
        throw Excepcion("Error: No hay ningun item almacenado en la posicion solicitada.");
    }
    return items[pos];
}

void Inventario::eliminar(unsigned int pos){
    if (pos >= LIMITE_INVENTARIO) return;
    items[pos] = itemNulo;
}

std::vector<Item*>* Inventario::obtenerTodosLosItems(){
    return &items;
}

void Inventario::eliminarTodosLosItems(){
    items.clear();
    items.resize(LIMITE_INVENTARIO, itemNulo);
}