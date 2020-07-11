#ifndef __ESTADO_MEDITACION_H__
#define __ESTADO_MEDITACION_H__
#include "Estado.h"

class EstadoMeditacion : public Estado{
    public:
    EstadoMeditacion(Personaje *unPersonaje); 
    //Ataque
    void atacar(Entidad *objetivo, Arma *arma) override;
    bool recibirDanio(int danio, Entidad *atacante) override;
    void serAtacadoPor(Entidad *atacante) override;
    //Otras acciones
    void meditar() override;
    void dejarDeMeditar() override;
    void actualizar(double tiempo) override;
    //Comercio
    void interactuar(Entidad *entidad) override;
    void pedirCuracion(Sacerdote *sacerdote, Cliente *cliente) override;
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    ~EstadoMeditacion() override;
};


#endif