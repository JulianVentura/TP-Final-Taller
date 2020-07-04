#include "FabricaDeItems.h"
#include "Item.h"
#include "Arma.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "Pocion.h"
#include "Oro.h"
#include "Pocion.h"

FabricaDeItems::FabricaDeItems(){
    //Do nothing
}
std::unique_ptr<Item> FabricaDeItems::obtenerItemAleatorio(std::string &idCriatura){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string idItem = "";
    unsigned int cantOro = 0;
    TipoItem result = config->calcularDrop(idCriatura);
    switch (result){
        case ARMA:
            idItem = config->calcularDropArma(idCriatura);
            if (idItem.length() == 0) return nullptr;           //No hay drop definido.
            return this->crearArma(idItem);
        case ARMADURA:
            idItem = config->calcularDropArmadura(idCriatura);
            if (idItem.length() == 0) return nullptr;           //No hay drop definido.
            return this->crearArmadura(idItem);
        case ESCUDO:
            idItem = config->calcularDropEscudo(idCriatura);
            if (idItem.length() == 0) return nullptr;           //No hay drop definido.
            return this->crearEscudo(idItem);
        case CASCO:
            idItem = config->calcularDropCasco(idCriatura);
            if (idItem.length() == 0) return nullptr;           //No hay drop definido.
            return this->crearCasco(idItem);
        case POCION:
            idItem = config->calcularDropPocion(idCriatura);
            if (idItem.length() == 0) return nullptr;           //No hay drop definido.
            return this->crearPocion(idItem);
        case ORO:
            cantOro = config->calcularDropOro(idCriatura);      
            return this->crearOro(cantOro);
        case NADA:{
            //Me tira warning si no manejo NADA.
        }
    }
    return nullptr;                                             //No hay drop
}
//Armas
std::unique_ptr<Arma> FabricaDeItems::crearArma(std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    int danioMax = config->obtenerArmaDanioMax(id);
    int danioMin = config->obtenerArmaDanioMin(id);
    float radioAtaque = config->obtenerArmaRangoAtaque(id);
    unsigned int consumoMana = config->obtenerArmaConsumoMana(id);
    return std::unique_ptr<Arma>(new Arma(danioMax, danioMin, consumoMana, radioAtaque, id));
}

//Armadura
std::unique_ptr<Armadura> FabricaDeItems::crearArmadura(std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerArmaduraDefensaMax(id);
    unsigned int defensaMin = config->obtenerArmaduraDefensaMin(id);
    return std::unique_ptr<Armadura>(new Armadura(defensaMax, defensaMin, id));
}
//Escudo
std::unique_ptr<Escudo> FabricaDeItems::crearEscudo(std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerEscudoDefensaMax(id);
    unsigned int defensaMin = config->obtenerEscudoDefensaMin(id);
    return std::unique_ptr<Escudo>(new Escudo(defensaMax, defensaMin, id));
}
//Casco
std::unique_ptr<Casco> FabricaDeItems::crearCasco(std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerCascoDefensaMax(id);
    unsigned int defensaMin = config->obtenerCascoDefensaMin(id);
    return std::unique_ptr<Casco>(new Casco(defensaMax, defensaMin, id));
}
//Pocion
std::unique_ptr<Pocion> FabricaDeItems::crearPocion(std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int curacionVida = config->obtenerPocionCuracionVida(id);
    unsigned int curacionMana = config->obtenerPocionCuracionMana(id);
    return std::unique_ptr<Pocion>(new Pocion(curacionVida, curacionMana, id));
}
//Oro
std::unique_ptr<Oro> FabricaDeItems::crearOro(unsigned int cantidad){
    return std::unique_ptr<Oro>(new Oro(cantidad));
}