#include "Portal.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#define ANCHO 4
#define ALTO 4

Portal::Portal(float x, float y) : Entidad("Portal#"), idMapa("mapa2"){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id_base = "Portal";
    uint32_t ancho = config->obtenerCiudadanoAncho(id_base);
    uint32_t alto = config->obtenerCiudadanoAlto(id_base);
    posicion = std::move(Posicion(x, y, ancho, alto));
}

void Portal::interactuar(Estado *estado, Cliente *cliente){
    cliente->cambiarDeMapa(idMapa);
}

void Portal::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){}

void Portal::comprar(unsigned int pos, Estado *estado, Cliente *cliente){}

void Portal::vender(unsigned int pos, Estado *estado, Cliente *cliente){}

void Portal::vender(Item* item, Personaje *personaje, Cliente *cliente){}

void Portal::listar(Personaje *personaje, Cliente *cliente){}

//Ataque

std::string Portal::atacar(Personaje *objetivo){ return "";}

std::string Portal::atacar(Criatura *objetivo){ return "";}

void Portal::serAtacadoPor(Personaje *atacante){}

void Portal::serAtacadoPor(Criatura *atacante){}

std::string Portal::recibirDanio(int danio, Entidad *atacante){ return "";}

//Estado

void Portal::actualizarEstado(double tiempo){}

void Portal::dropearItems(Entidad *atacante){}

Portal::~Portal(){

}