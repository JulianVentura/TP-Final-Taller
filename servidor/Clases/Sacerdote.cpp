#include "Sacerdote.h"
#include "FabricaDeItems.h"
#include "Item.h"
#include "Pocion.h"
#include "Casco.h"
#include "Escudo.h"
#include "Armadura.h"
#include "Arma.h"
#include "Cliente.h"
#include "Estado.h"
#include "Divulgador.h"
#include "Personaje.h"


Sacerdote::Sacerdote(float x, float y) : Comerciante(x, y){
    id = "Sacerdote#";
    std::string id_base = "Sacerdote";
    items.clear();
    items.resize(TAM_TIENDA, itemNulo);
    unsigned int cont = 0;
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::vector<std::string> idItems = config->obtenerCiudadanoStockArmas(id_base);
    for (auto &idArma : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearArma(idArma);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockArmaduras(id_base);
    for (auto &idArmadura : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearArma(idArmadura);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockEscudos(id_base);
    for (auto &idEscudo : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearEscudo(idEscudo);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockCascos(id_base);
    for (auto &idCasco : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearCasco(idCasco);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockPociones(id_base);
    for (auto &idPocion : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearPocion(idPocion);
        cont++;
    }
}

//Ataque

void Sacerdote::serAtacadoPor(Personaje *personaje){
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    std::string mensaje;
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        mensaje = "La distancia es muy grande";
        divulgador->encolarMensaje(personaje->obtenerId(), mensaje);
        return;
    }
    personaje->sanar();
    mensaje = "Ha sido curado";
    divulgador->encolarMensaje(personaje->obtenerId(), mensaje);
}

Sacerdote::~Sacerdote(){

}