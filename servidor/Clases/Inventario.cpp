#include "Inventario.h"
#include "Excepcion.h"

//Ver si es necesario levantar el limite de items del archivo de configuraciones

Inventario::Inventario() : limiteItems(0), items(){}


void Inventario::almacenar(std::unique_ptr<Item> item){
    if (items.size() == limiteItems){
        throw Excepcion
        ("Error: Se ha intentado almacenar un nuevo item, pero el inventario esta lleno.");
    }
    items.push_back(std::move(item));
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
    for (auto &item : items){
        resultado.push_back(item.get()->obtenerId());
    }
    return resultado;
}