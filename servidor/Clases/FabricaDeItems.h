#ifndef __FABRICA_DE_ITEMS_H__
#define __FABRICA_DE_ITEMS_H__
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
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
    std::unordered_set<std::string> armasCuracion;
    std::unique_ptr<ItemNulo> itemNulo;
    std::unordered_map<int, std::string> conversor;
    unsigned int limiteArmas;
    unsigned int limiteArmaduras;
    unsigned int limiteCascos;
    unsigned int limiteEscudos;
    unsigned int limitePociones;

    std::mutex mutex;

    static void crearInstancia();

    bool esArmaDeCuracion(const std::string &id) const;
    Arma* crearArmaCuracion(const std::string &id);
    public:
    Item* obtenerItemAleatorio(const std::string &idCriatura);
    /*
    Devuelve un puntero a Item dado el idTCP pasado por parametro, esta operacion es mas costosa que
    llamar directamente a los metodos de creacion de items por categoria ya que debera realizar un parseo
    basandose en los limites de ids configurados en el archivo de configuraciones.
    */
    Item* obtenerItemIDTCP(const uint16_t id);
    Item* crearItemNulo();
    static FabricaDeItems* obtenerInstancia();

    //Arma
    /*
    Devuelve un puntero a Arma que corresponde a una instancia de Arma con el id solicitado.
    Si dicha instancia ya ha sido creada se devuelve una copia del puntero, caso contrario
    se crea una nueva instancia y se devuelve el puntero.
    */
    Arma* crearArma(const std::string &id);
    //Armadura
    /*
    Devuelve un puntero a Armadura que corresponde a una instancia de Armadura con el id solicitado.
    Si dicha instancia ya ha sido creada se devuelve una copia del puntero, caso contrario
    se crea una nueva instancia y se devuelve el puntero.
    */
    Armadura* crearArmadura(const std::string &id);
    
    //Escudo
    /*
    Devuelve un puntero a Escudo que corresponde a una instancia de Escudo con el id solicitado.
    Si dicha instancia ya ha sido creada se devuelve una copia del puntero, caso contrario
    se crea una nueva instancia y se devuelve el puntero.
    */
    Escudo* crearEscudo(const std::string &id);
    //Casco
    /*
    Devuelve un puntero a Casco que corresponde a una instancia de Casco con el id solicitado.
    Si dicha instancia ya ha sido creada se devuelve una copia del puntero, caso contrario
    se crea una nueva instancia y se devuelve el puntero.
    */
    Casco* crearCasco(const std::string &id);
    //Pocion
    /*
    Devuelve un puntero a Pocion que corresponde a una instancia de Pocion con el id solicitado.
    Si dicha instancia ya ha sido creada se devuelve una copia del puntero, caso contrario
    se crea una nueva instancia y se devuelve el puntero.
    */
    Pocion* crearPocion(const std::string &id);
    
    private:
    FabricaDeItems();
    static FabricaDeItems instancia;
    static bool instanciaCreada;
};
#endif
