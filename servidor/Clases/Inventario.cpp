#include "Inventario.h"
#include "Excepcion.h"
#define LIMITE_INVENTARIO 20
//Ver si es necesario levantar el limite de items del archivo de configuraciones

Inventario::Inventario() : limiteItems(LIMITE_INVENTARIO), items(limiteItems){}


Inventario& Inventario::operator=(Inventario &&otro){
    this->items = std::move(otro.items);
    this->limiteItems = std::move(otro.limiteItems);
    return *this;
}

void Inventario::almacenar(std::unique_ptr<Item> item){
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
    if (!items[pos]){
        throw Excepcion("Error: No hay ningun item almacenado en la posicion solicitada.");
    }
    return items[pos].get();
}

void Inventario::eliminar(unsigned int pos){
    items[pos] = nullptr;
}

std::vector<std::string> Inventario::obtenerTodosLosItems(){
    std::vector<std::string> resultado;
    for (std::size_t i=0; i<items.size(); i++){
        if (!items[i]){
            resultado.push_back("Vacio");
        }else{
            resultado.push_back(items[i]->obtenerId());
        }
    }
    return resultado;
}