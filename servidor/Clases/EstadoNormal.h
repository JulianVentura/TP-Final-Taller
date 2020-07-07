#ifndef __ESTADO_NORMAL_H__
#define __ESTADO_NORMAL_H__
#include "Estado.h"

class EstadoNormal : public Estado{
    public:
    EstadoNormal(Personaje *unPersonaje); 
    void interactuar(Entidad *entidad) override;
    void atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador) override;
    void actualizar(double tiempo, Mapa *mapa) override;
    void recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador) override;
    void meditar() override;
    void dejarDeMeditar() override;
    void pedirCuracion(Sacerdote *sacerdote, Cliente *cliente) override;
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;

    ~EstadoNormal() override;
};


#endif