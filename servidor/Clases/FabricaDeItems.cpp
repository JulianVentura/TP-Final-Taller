#include "FabricaDeItems.h"
#include "Configuraciones.h"
#include "Excepcion.h"
#include "Item.h"
#include "Arma.h"
#include "ArmaCuracion.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "Pocion.h"


FabricaDeItems FabricaDeItems::instancia;
bool FabricaDeItems::instanciaCreada = false;

FabricaDeItems* FabricaDeItems::obtenerInstancia(){
    if (!instanciaCreada){
        crearInstancia();
    }
    return &instancia;
}

void FabricaDeItems::crearInstancia(){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    instancia.limiteArmas = config->obtenerFabricaDeItemsLimiteArmas();
    instancia.limiteArmaduras = config->obtenerFabricaDeItemsLimiteArmaduras();
    instancia.limiteCascos = config->obtenerFabricaDeItemsLimiteCascos();
    instancia.limiteEscudos = config->obtenerFabricaDeItemsLimiteEscudos();
    instancia.limitePociones = config->obtenerFabricaDeItemsLimitePociones();
    instancia.conversor = std::move(config->obtenerFabricaDeItemsConversor());
    instancia.armasCuracion = std::move(config->obtenerFabricaDeItemsArmasDeCuracion());
    instanciaCreada = true;
}

FabricaDeItems::FabricaDeItems(){
    limiteArmas = 0;
    limiteArmaduras = 0;
    limiteCascos = 0;
    limiteEscudos = 0;
    limitePociones = 0;
    itemNulo = nullptr;
}

Item* FabricaDeItems::obtenerItemAleatorio(const std::string &idCriatura){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string idItem = "";
    TipoItem result = config->calcularDropItem(idCriatura);
    switch (result){
        case ARMA:
            idItem = config->calcularDropArma(idCriatura);
            if (idItem.length() == 0) return itemNulo.get();           //No hay drop definido.
            return this->crearArma(idItem);
        case ARMADURA:
            idItem = config->calcularDropArmadura(idCriatura);
            if (idItem.length() == 0) return itemNulo.get();           //No hay drop definido.
            return this->crearArmadura(idItem);
        case ESCUDO:
            idItem = config->calcularDropEscudo(idCriatura);
            if (idItem.length() == 0) return itemNulo.get();           //No hay drop definido.
            return this->crearEscudo(idItem);
        case CASCO:
            idItem = config->calcularDropCasco(idCriatura);
            if (idItem.length() == 0) return itemNulo.get();           //No hay drop definido.
            return this->crearCasco(idItem);
        case POCION:
            idItem = config->calcularDropPocion(idCriatura);
            if (idItem.length() == 0) return itemNulo.get();           //No hay drop definido.
            return this->crearPocion(idItem);
    }
    return itemNulo.get();                                      //No hay drop
}
//Armas
Arma* FabricaDeItems::crearArma(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Arma>>::iterator it = armas.find(id);
    if (it != armas.end()){
        return it->second.get();
    }else if (esArmaDeCuracion(id)){
        return crearArmaCuracion(id);
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    int danioMax = config->obtenerArmaDanioMax(id);
    int danioMin = config->obtenerArmaDanioMin(id);
    float radioAtaque = config->obtenerArmaRangoAtaque(id);
    double tiempoAtaque = config->obtenerArmaTiempoAtaque(id);
    unsigned int consumoMana = config->obtenerArmaConsumoMana(id);
    unsigned int precio = config->obtenerArmaPrecio(id);
    uint16_t idTCP = config->obtenerArmaIDTCP(id);
    std::string idProyectil = config->obtenerArmaIDProyectil(id);
    armas[id] = std::unique_ptr<Arma>(new Arma(danioMax, 
                                               danioMin, 
                                               consumoMana, 
                                               radioAtaque, 
                                               tiempoAtaque, 
                                               id,
                                               idProyectil, 
                                               idTCP, 
                                               precio));
    return armas[id].get();
}

Arma* FabricaDeItems::crearArmaCuracion(const std::string &id){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    uint32_t curacionMax = config->obtenerArmaCuracionMax(id);
    uint32_t curacionMin = config->obtenerArmaCuracionMin(id);
    float radioAtaque = config->obtenerArmaRangoAtaque(id);
    double tiempoAtaque = config->obtenerArmaTiempoAtaque(id);
    uint32_t consumoMana = config->obtenerArmaConsumoMana(id);
    uint32_t precio = config->obtenerArmaPrecio(id);
    uint16_t idTCP = config->obtenerArmaIDTCP(id);
    std::string idProyectil = config->obtenerArmaIDProyectil(id);
    armas[id] = std::unique_ptr<Arma>(new ArmaCuracion(curacionMax, 
                                                       curacionMin, 
                                                       consumoMana, 
                                                       radioAtaque, 
                                                       tiempoAtaque, 
                                                       id,
                                                       idProyectil, 
                                                       idTCP, 
                                                       precio));
    return armas[id].get();
}

//Armadura
Armadura* FabricaDeItems::crearArmadura(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Armadura>>::iterator it = armaduras.find(id);
    if (it != armaduras.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerArmaduraDefensaMax(id);
    unsigned int defensaMin = config->obtenerArmaduraDefensaMin(id);
    unsigned int precio = config->obtenerArmaduraPrecio(id);
    uint16_t idTCP = config->obtenerArmaduraIDTCP(id);
    armaduras[id] = std::unique_ptr<Armadura>(new Armadura(defensaMax, defensaMin, id, idTCP, precio));
    return armaduras[id].get();
}
//Escudo
Escudo* FabricaDeItems::crearEscudo(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Escudo>>::iterator it = escudos.find(id);
    if (it != escudos.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerEscudoDefensaMax(id);
    unsigned int defensaMin = config->obtenerEscudoDefensaMin(id);
    unsigned int precio = config->obtenerEscudoPrecio(id);
    uint16_t idTCP = config->obtenerEscudoIDTCP(id);
    escudos[id] = std::unique_ptr<Escudo>(new Escudo(defensaMax, defensaMin, id, idTCP, precio));
    return escudos[id].get();
}
//Casco
Casco* FabricaDeItems::crearCasco(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Casco>>::iterator it = cascos.find(id);
    if (it != cascos.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int defensaMax = config->obtenerCascoDefensaMax(id);
    unsigned int defensaMin = config->obtenerCascoDefensaMin(id);
    unsigned int precio = config->obtenerCascoPrecio(id);
    uint16_t idTCP = config->obtenerCascoIDTCP(id);
    cascos[id] = std::unique_ptr<Casco>(new Casco(defensaMax, defensaMin, id, idTCP, precio));
    return cascos[id].get();
}
//Pocion
Pocion* FabricaDeItems::crearPocion(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, std::unique_ptr<Pocion>>::iterator it = pociones.find(id);
    if (it != pociones.end()){
        return it->second.get();
    }
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int curacionVida = config->obtenerPocionCuracionVida(id);
    unsigned int curacionMana = config->obtenerPocionCuracionMana(id);
    unsigned int precio = config->obtenerPocionPrecio(id);
    uint16_t idTCP = config->obtenerPocionIDTCP(id);
    pociones[id] = std::unique_ptr<Pocion>(new Pocion(curacionVida, curacionMana, id, idTCP, precio));
    return pociones[id].get();
}

Item* FabricaDeItems::crearItemNulo(){
    if (!itemNulo){
        Configuraciones *config = Configuraciones::obtenerInstancia();
        uint16_t precio = config->obtenerItemNuloPrecio();
        uint16_t idTCP = config->obtenerItemNuloIDTCP();
        itemNulo = std::move(std::unique_ptr<ItemNulo>(new ItemNulo("ItemNulo", idTCP, precio)));
    }
    return itemNulo.get();
}

Item* FabricaDeItems::obtenerItemIDTCP(uint16_t idTCP){
    std::string idString = conversor[idTCP];

    if (idTCP == 0) return crearItemNulo();

    if (idTCP <= limiteArmas){
        return crearArma(idString);
    }
    if (idTCP > limiteArmas && idTCP <= limiteArmaduras){
        return crearArmadura(idString);
    }
    if (idTCP > limiteArmas && idTCP <= limiteCascos){
        return crearCasco(idString);
    }
    if (idTCP > limiteCascos && idTCP <= limiteEscudos){
        return crearEscudo(idString);
    }
    if (idTCP > limiteEscudos && idTCP <= limitePociones){
        return crearPocion(idString);
    }
    //Si se llego aca es porque el id es erroneo
    throw Excepcion("Error al fabricar item: El id %u es erroneo", idTCP);
}


bool FabricaDeItems::esArmaDeCuracion(const std::string &id) const{
    std::unordered_set<std::string>::const_iterator it = armasCuracion.find(id);
    if (it == armasCuracion.end()) return false;
    return true;
}
