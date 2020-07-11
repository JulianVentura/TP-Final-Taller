#ifndef __ARMA_H__
#define __ARMA_H__
#include "Configuraciones.h"
#include "Item.h"
#include "Reloj.h"

class Mapa;
class Entidad;
class Arma : public Item{
    private:
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
    void atacar(Entidad *objetivo, Entidad *atacante, Mapa *mapa);
    void utilizar(Personaje *personaje, unsigned int pos) override;
    void desequipar(Personaje *personaje) override;
    friend class Configuraciones;
};


#endif
