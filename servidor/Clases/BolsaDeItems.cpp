#include "BolsaDeItems.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "FabricaDeItems.h"
#include <sstream>
#include "Excepcion.h"

#define TAM_ALMACEN 18

static unsigned int contadorDeInstancias = 0;

BolsaDeItems::BolsaDeItems(Posicion unaPosicion, Item *item) : 
                                                            Interactuable(""),
                                                            elementos(1),
                                                            bolsaVacia(false){
    std::stringstream nuevoId;
    nuevoId << "BolsaDeItems#" << contadorDeInstancias;
    contadorDeInstancias++;
    id = nuevoId.str(); 
    items.push_back(item);
    this->posicion.actualizarPosicion(std::move(unaPosicion));
}

BolsaDeItems::BolsaDeItems(Posicion unaPosicion, std::vector<Item*> unosItems) :
                                                           Interactuable(""),
                                                           items(std::move(unosItems)),
                                                           elementos(0),
                                                           bolsaVacia(true){
    std::stringstream nuevoId;
    nuevoId << "BolsaDeItems#" << contadorDeInstancias;
    contadorDeInstancias++;
    id = nuevoId.str(); 
    for (auto &item : items){
        if (item != nullptr) elementos++;
    }
    if (elementos > 0) bolsaVacia = false;
    this->posicion.actualizarPosicion(std::move(unaPosicion));
}

void BolsaDeItems::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}
void BolsaDeItems::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}
void BolsaDeItems::vender(Item* item, Estado *estado, Cliente *cliente){
    estado->pedirVenta(item, this, cliente);
}

void BolsaDeItems::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    if (pos >= TAM_ALMACEN || items[pos] == nullptr){
        //No hay nada que entregarle
        return;
    }
    personaje->almacenar(items[pos]);
    //Si falla al almacenar no se pisa el puntero
    items[pos] = nullptr;
    elementos--;
    if (elementos <= 0) bolsaVacia = true;
    cliente -> enviarInventario();
    cliente -> enviarContenedor(items);
}
void BolsaDeItems::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //No se puede almacenar un item en una bolsa de items, se le avisa a usuario?
    //No, no se le avisa.
}
void BolsaDeItems::listar(Personaje *personaje, Cliente *cliente){
    cliente -> enviarContenedor(items);
}

bool BolsaDeItems::estaVacia(){
    return bolsaVacia;
}

BolsaDeItems::~BolsaDeItems(){

}