#ifndef __ESTADO_FANTASMA_H__
#define __ESTADO_FANTASMA_H__
#include "Estado.h"

class EstadoFantasma : public Estado{
    public:
    EstadoFantasma(Personaje *unPersonaje); 
    void interactuar(Entidad *entidad) override;
    void atacar(Entidad *objetivo, Arma *arma) override;
    void actualizar(double tiempo, Mapa *mapa) override;
    void recibirDanio(int danio, Entidad *atacante) override;
    //void interactuar(Sacerdote *sacerdote);
    //void interactuar(Banquero *banquero);
    //void interactuar(Comerciante *comerciante);
    //void interactuar(Personaje *personaje);
    //void interactuar(Criatura *criatura);
    void meditar() override;
    void dejarDeMeditar() override;

    ~EstadoFantasma() override;

};

#endif