#ifndef __ARMA_H__
#define __ARMA_H__
#include "Configuraciones.h"
#include "Item.h"
#include "Reloj.h"
#define ATAQUE_NO_REALIZADO -1


class Mapa;
class Entidad;
class Arma : public Item{
    protected:
    unsigned int danioMax;
    unsigned int danioMin;
    unsigned int consumoMana;
    std::string proyectil;
    float radioAtaque;
    double tiempoAtaque;
    double tiempoTranscurrido;
    Reloj reloj;
    
    public:
    Arma(int danioMax, 
         int danioMin, 
         unsigned int consMana, 
         float radioAtaque,
         double tiempoAtaque, 
         std::string id,
         std::string idProyectil,
         uint16_t idTCP,
         unsigned int unPrecio);
    Arma(Arma &otro) = delete;
    Arma(Arma &&otro) = delete;
    Arma& operator=(Arma &otro) = delete;
    Arma& operator=(Arma &&otro) = delete;
    /*
    Efectua el ataque al objetivo y devuelve un mensaje con el resultado obtenido.
    El ataque no se realiza si el mana del atacante es inferior al necesario por el arma o si
    la distancia entre el atacante y objetivo es mayor al rango del arma. En ambos casos se devuelve
    un mensaje descriptivo.
    Una vez efectuado el ataque se creara una instancia de Proyectil que sera cargada en el mapa.
    El arma no permite realizar ataques a uno mismo, en tal caso se devuelve una cadena vacia.
    */
    virtual std::string atacar(Entidad *objetivo, Entidad *atacante, Mapa *mapa);
    /*
    Indica al personaje que debe equipar este arma situada en la posicion pos del inventario.
    */
    void utilizar(Personaje *personaje, unsigned int pos) override;
    /*
    Indica al personaje que debe desequipar este arma situada en la posicion pos del inventario.
    */
    void desequipar(Personaje *personaje, unsigned int pos) override;
    friend class Configuraciones;
};


#endif
