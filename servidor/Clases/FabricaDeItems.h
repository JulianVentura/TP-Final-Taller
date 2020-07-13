#ifndef __FABRICA_DE_ITEMS_H__
#define __FABRICA_DE_ITEMS_H__
#include <memory>
#include <mutex>
#include <unordered_map>
#include "ItemNulo.h"
class Item;
class Pocion;
class Arma;
class Armadura;
class Casco;
class Escudo;
class FabricaDeItems{

    private:
    std::unordered_map<std::string, std::unique_ptr<Arma>> armas;
    std::unordered_map<std::string, std::unique_ptr<Armadura>> armaduras;
    std::unordered_map<std::string, std::unique_ptr<Casco>> cascos;
    std::unordered_map<std::string, std::unique_ptr<Escudo>> escudos;
    std::unordered_map<std::string, std::unique_ptr<Pocion>> pociones;
    std::unique_ptr<ItemNulo> itemNulo;
    std::unordered_map<int, std::string> conversor;
    unsigned int limiteArmas;
    unsigned int limiteArmaduras;
    unsigned int limiteCascos;
    unsigned int limiteEscudos;
    unsigned int limitePociones;

    std::mutex mutex;

    static void crearInstancia();

    public:
    Item* obtenerItemAleatorio(std::string &idCriatura);
    Item* obtenerItemIDTCP(uint16_t id);
    Item* crearItemNulo();
    static FabricaDeItems* obtenerInstancia();

    //Arma
    Arma* crearArma(std::string &id);
    //Armadura
    Armadura* crearArmadura(std::string &id);
    //Escudo
    Escudo* crearEscudo(std::string &id);
    //Casco
    Casco* crearCasco(std::string &id);
    //Pocion
    Pocion* crearPocion(std::string &id);
    
    private:
    FabricaDeItems();
    static FabricaDeItems instancia;
    static bool instanciaCreada;
};
#endif
