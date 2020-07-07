#include "FabricaDeItems.h"
#include "Item.h"
#include "Arma.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "Pocion.h"


FabricaDeItems FabricaDeItems::instancia;

FabricaDeItems* FabricaDeItems::obtenerInstancia(){
    return &instancia;
}

FabricaDeItems::FabricaDeItems(){
    //Do nothing
}
Item* FabricaDeItems::obtenerItemAleatorio(std::string &idCriatura){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string idItem = "";
    TipoItem result = config->calcularDropItem(idCriatura);
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
    }
    return nullptr;                                             //No hay drop
}
//Armas
Arma* FabricaDeItems::crearArma(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Arma>>::iterator it = armas.find(id);
    if (it != armas.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    int danioMax = config->obtenerArmaDanioMax(id);
    int danioMin = config->obtenerArmaDanioMin(id);
    float radioAtaque = config->obtenerArmaRangoAtaque(id);
    unsigned int consumoMana = config->obtenerArmaConsumoMana(id);
    unsigned int precio = config->obtenerArmaPrecio(id);
    armas[id] = std::unique_ptr<Arma>(new Arma(danioMax, danioMin, consumoMana, radioAtaque, id, precio));
    return armas[id].get();
}

//Armadura
Armadura* FabricaDeItems::crearArmadura(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Armadura>>::iterator it = armaduras.find(id);
    if (it != armaduras.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerArmaduraDefensaMax(id);
    unsigned int defensaMin = config->obtenerArmaduraDefensaMin(id);
    unsigned int precio = config->obtenerArmaduraPrecio(id);
    armaduras[id] = std::unique_ptr<Armadura>(new Armadura(defensaMax, defensaMin, id, precio));
    return armaduras[id].get();
}
//Escudo
Escudo* FabricaDeItems::crearEscudo(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Escudo>>::iterator it = escudos.find(id);
    if (it != escudos.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerEscudoDefensaMax(id);
    unsigned int defensaMin = config->obtenerEscudoDefensaMin(id);
    unsigned int precio = config->obtenerEscudoPrecio(id);
    escudos[id] = std::unique_ptr<Escudo>(new Escudo(defensaMax, defensaMin, id, precio));
    return escudos[id].get();
}
//Casco
Casco* FabricaDeItems::crearCasco(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Casco>>::iterator it = cascos.find(id);
    if (it != cascos.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerCascoDefensaMax(id);
    unsigned int defensaMin = config->obtenerCascoDefensaMin(id);
    unsigned int precio = config->obtenerCascoPrecio(id);
    cascos[id] = std::unique_ptr<Casco>(new Casco(defensaMax, defensaMin, id, precio));
    return cascos[id].get();
}
//Pocion
Pocion* FabricaDeItems::crearPocion(std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Pocion>>::iterator it = pociones.find(id);
    if (it != pociones.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int curacionVida = config->obtenerPocionCuracionVida(id);
    unsigned int curacionMana = config->obtenerPocionCuracionMana(id);
    unsigned int precio = config->obtenerPocionPrecio(id);
    pociones[id] = std::unique_ptr<Pocion>(new Pocion(curacionVida, curacionMana, id, precio));
    return pociones[id].get();
}
/*
//Oro
std::unique_ptr<Oro> FabricaDeItems::crearOro(unsigned int cantidad){
    return std::unique_ptr<Oro>(new Oro(cantidad));
}
*/