#include "Sacerdote.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#define ANCHO 4
#define ALTO 4

Sacerdote::Sacerdote(float x, float y) : Entidad("Sacerdote#"){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id_base = "Sacerdote";
    uint32_t ancho = config->obtenerCiudadanoAncho(id_base);
    uint32_t alto = config->obtenerCiudadanoAlto(id_base);
    posicion = std::move(Posicion(x, y, ancho, alto));
}

void Sacerdote::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirCuracion(this, cliente);
}

void Sacerdote::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    //El sacerdote no vende
}

void Sacerdote::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    //El sacerdote no vende
}

void Sacerdote::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    //El sacerdote no compra
}

void Sacerdote::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //El sacerdote no compra
}

void Sacerdote::listar(Personaje *personaje, Cliente *cliente){
    //El sacerdote no tiene items.
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


//Ataque

void Sacerdote::atacar(Personaje *objetivo){
    //Nada
}

void Sacerdote::atacar(Criatura *objetivo){
    //Nada
}

void Sacerdote::serAtacadoPor(Entidad *atacante){
    //Nada
}

void Sacerdote::serAtacadoPor(Personaje *atacante){
    //Nada
}

void Sacerdote::serAtacadoPor(Criatura *atacante){
    //Nada
}

bool Sacerdote::recibirDanio(int danio, Entidad *atacante){
    return false;
}

//Estado

void Sacerdote::actualizarEstado(double tiempo){
    //Nada
}

void Sacerdote::dropearItems(Entidad *atacante){
    //Nada
}

Sacerdote::~Sacerdote(){

}