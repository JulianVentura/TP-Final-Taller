#include "Comerciante.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "Arma.h"
#include "Armadura.h"
#include "Casco.h"
#include "Escudo.h"
#include "Pocion.h"
#include "FabricaDeItems.h"

#define ANCHO 4
#define ALTO 4

Comerciante::Comerciante(float x, float y) : Interactuable("Comerciante"){
    //Si, esta re hardcodeado. La idea es que esto se levante del archivo de config.
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    std::string idItem = "Espada";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "Hacha";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "Martillo";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "VaraDeFresno";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "ArmaduraDeCuero";
    items.push_back(fabrica->crearArmadura(idItem));
    idItem = "ArmaduraDePlacas";
    items.push_back(fabrica->crearArmadura(idItem));
    idItem = "Capucha";
    items.push_back(fabrica->crearCasco(idItem));
    idItem = "EscudoDeTortuga";
    items.push_back(fabrica->crearEscudo(idItem));
    idItem = "PocionVida";
    items.push_back(fabrica->crearPocion(idItem));
    idItem = "PocionMana";
    items.push_back(fabrica->crearPocion(idItem));
    posicion = std::move(Posicion(x, y, ANCHO, ALTO));
}

void Comerciante::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}
void Comerciante::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}
void Comerciante::vender(Item* item, Estado *estado, Cliente *cliente){
    estado->pedirVenta(item, this, cliente);
}

void Comerciante::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    if (pos >= items.size() || items[pos] == nullptr){
        //No hay nada que comprar
        return;
    }
    if (personaje->tieneOroSuficiente(items[pos]->obtenerPrecio())){
        personaje->almacenar(items[pos]);
        personaje->restarOro(items[pos]->obtenerPrecio());
    }else{
        //Indicarle que no se le puede vender.
    }
}
void Comerciante::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    personaje->recibirOro(item->obtenerPrecio());
}
void Comerciante::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    //cliente.enviarTienda(items);
}


Comerciante::~Comerciante(){}