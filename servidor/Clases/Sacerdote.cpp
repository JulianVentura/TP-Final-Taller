#include "Sacerdote.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#define ANCHO 4
#define ALTO 4

Sacerdote::Sacerdote(float x, float y) : Interactuable("Sacerdote"){
    //Esto se tiene que levantar del configuraciones.json
    posicion = std::move(Posicion(x, y, ANCHO, ALTO));
}

void Sacerdote::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirCuracion(this, cliente);
}

void Sacerdote::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    //El sacerdote no vende
}

void Sacerdote::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    //El sacerdote no compra
}

void Sacerdote::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    //El sacerdote no vende
}

void Sacerdote::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //El sacerdote no compra
}

void Sacerdote::listar(Personaje *personaje, Cliente *cliente){
    //El sacerdote no tiene items
}

void Sacerdote::curar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return;
    }
    //Se le tiene que mandar algun mensaje?
    personaje->curar();
}

Sacerdote::~Sacerdote(){

}