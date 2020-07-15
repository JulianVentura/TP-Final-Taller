#include "Sacerdote.h"
#include "FabricaDeItems.h"
#include "Item.h"
#include "Pocion.h"
#include "Arma.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"


Sacerdote::Sacerdote(float x, float y) : Comerciante(x, y){
    id = "Sacerdote#";
    items.clear();
    items.resize(tamTienda, itemNulo);
    unsigned int cont = 0;
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    std::string idItem = "VaraDeFresno";
    items[cont] = fabrica->crearArma(idItem);
    cont++;
    idItem = "PocionVida";
    items[cont] = fabrica->crearPocion(idItem);
    cont++;
    idItem = "PocionMana";
    items[cont] = fabrica->crearPocion(idItem);
    cont++;
}

bool Sacerdote::curar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return false;
    }
    personaje->curar();
    std::string mensaje = "Ha sido curado";
    cliente->enviarChat(mensaje, false);
    return true;
}


//Ataque

void Sacerdote::serAtacadoPor(Personaje *atacante){
    atacante->curar();
}

Sacerdote::~Sacerdote(){

}