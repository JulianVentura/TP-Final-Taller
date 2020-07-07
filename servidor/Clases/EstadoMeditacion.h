#ifndef __ESTADO_MEDITACION_H__
#define __ESTADO_MEDITACION_H__
#include "Estado.h"

class EstadoMeditacion : public Estado{
    public:
    EstadoMeditacion(Personaje *unPersonaje); 
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
    ~EstadoMeditacion() override;
};


#endif