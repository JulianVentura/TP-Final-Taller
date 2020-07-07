#ifndef __ARMA_H__
#define __ARMA_H__
#include "Configuraciones.h"
#include "Item.h"
class Divulgador;
class Entidad;
class Arma : public Item{
    private:
    unsigned int danioMax;
    unsigned int danioMin;
    unsigned int consumoMana;
    float radioAtaque;
    
    public:
    Arma(int danioMax, 
         int danioMin, 
         unsigned int consMana, 
         float radioAtaque, 
         std::string id,
         uint16_t idTCP,
         unsigned int unPrecio);
    Arma(Arma &otro) = delete;
    Arma(Arma &&otro) = delete;
    Arma& operator=(Arma &otro) = delete;
    Arma& operator=(Arma &&otro) = delete;
    void atacar(Entidad *objetivo, Entidad *atacante, Divulgador *divulgador);
    void utilizar(Personaje *personaje, unsigned int pos) override;
    friend class Configuraciones;
};


#endif
