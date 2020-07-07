#include "Inventario.h"
#include "BolsaDeItems.h"
#include "Excepcion.h"
//Esto deberia sincronizarse con el cliente, un define en un common.
#define LIMITE_INVENTARIO 18
//Ver si es necesario levantar el limite de items del archivo de configuraciones

Inventario::Inventario() : limiteItems(LIMITE_INVENTARIO), items(limiteItems, nullptr){}


Inventario& Inventario::operator=(Inventario &&otro){
    this->items = std::move(otro.items);
    this->limiteItems = std::move(otro.limiteItems);
    return *this;
}

void Inventario::almacenar(Item* item){
    bool almacenado = false;
    for (std::size_t i=0; i<items.size(); i++){
        if (!items[i]){
            items[i] = std::move(item);
            almacenado = true;
            break;
        }
    }
    if (!almacenado){
        throw Excepcion
        ("Error: Se ha intentado almacenar un nuevo item, pero el inventario esta lleno.");
    }
}

Item* Inventario::obtenerItem(unsigned int pos){
    if (pos >= LIMITE_INVENTARIO || !items[pos]){
        throw Excepcion("Error: No hay ningun item almacenado en la posicion solicitada.");
    }
    return items[pos];
}

void Inventario::eliminar(unsigned int pos){
    if (pos >= LIMITE_INVENTARIO) return;
    items[pos] = nullptr;
}

std::vector<Item*>* Inventario::obtenerTodosLosItems(){
    return &items;
}

void Inventario::eliminarTodosLosItems(){
    items.clear();
    items.resize(LIMITE_INVENTARIO, nullptr);
}