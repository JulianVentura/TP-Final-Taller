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

void Banquero::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirVenta(pos, this, cliente);
}

void Banquero::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return;
    }
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    if (pos >= TAM_ALMACEN || almacen[pos] == nullptr){
        //No hay nada que entregarle
        return;
    }
    Item *temp = almacen[pos];
    personaje->almacenar(almacen[pos]);
    almacen[pos] = nullptr;
    cliente -> enviarInventario();
    cliente -> enviarContenedor(almacen);
    std::string mensaje = "Se recibio " + temp->obtenerId();
    cliente->enviarChat(mensaje, false);
}

void Banquero::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        personaje->almacenar(item);
        return;
    }
    //Comprarle el item que pide y notificarle a cliente
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    bool almacenado = false;
    for (std::size_t i=0; i<TAM_ALMACEN; i++){
        if (almacen[i] == nullptr){
            almacen[i] = item;
            almacenado = true;
            break;
        }
    }
    if (!almacenado){
        std::string mensaje = "No hay espacio para almacenar mas items en el banquero";
        cliente->enviarChat(mensaje, false);
        throw Excepcion("Error: No hay espacio para almacenar mas items en el banquero");
    }
    cliente -> enviarInventario();
    cliente -> enviarContenedor(almacen);
    std::string mensaje = "Se almaceno " + item->obtenerId();
    cliente->enviarChat(mensaje, false);
}
void Banquero::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return;
    }
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    cliente -> enviarContenedor(almacen);
}


Banquero::~Banquero(){

}