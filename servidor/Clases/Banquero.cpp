#include "Banquero.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "FabricaDeItems.h"
#include "Excepcion.h"

#define TAM_ALMACEN 18

#define ANCHO 4
#define ALTO 4

Banquero::Banquero(float x, float y) : Interactuable("Banquero"){
    //Esto se tiene que levantar del configuraciones.json
    posicion = std::move(Posicion(x, y, ANCHO, ALTO));
}

void Banquero::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}

void Banquero::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}

void Banquero::vender(Item* item, Estado *estado, Cliente *cliente){
    estado->pedirVenta(item, this, cliente);
}

void Banquero::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    std::vector<Item*> almacen = personaje->obtenerAlmacen();
    if (pos >= TAM_ALMACEN || almacen[pos] == nullptr){
        //No hay nada que entregarle
        return;
    }
    personaje->almacenar(almacen[pos]);
    almacen[pos] = nullptr;
}

void Banquero::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    //Comprarle el item que pide y notificarle a cliente
    std::vector<Item*> almacen = personaje->obtenerAlmacen();
    bool almacenado = false;
    for (std::size_t i=0; i<TAM_ALMACEN; i++){
        if (almacen[i] == nullptr){
            almacen[i] = item;
            almacenado = true;
        }
    }
    if (!almacenado){
        throw Excepcion("Error: No hay espacio para almacenar mas items en el banquero");
    }
}
void Banquero::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    //cliente.enviarContenedor(items)
}


Banquero::~Banquero(){

}