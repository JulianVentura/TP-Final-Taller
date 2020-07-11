#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Movible.h"
#include "Interactuable.h"
#include "Configuraciones.h"
#include "Inventario.h"
#include "PosicionEncapsulada.h"
#include <string>

class Mapa;
class Entidad : public Interactuable{
    protected:
    int vidaMaxima;
    int vidaActual;
    int manaMaximo;
    int manaActual;
    unsigned int fuerza;
    unsigned int inteligencia;
    unsigned int agilidad;
    unsigned int constitucion;
    unsigned int nivel;
    Mapa *mapaAlQuePertenece;

    public:
    virtual ~Entidad();
    Entidad(std::string id);
    virtual void actualizarEstado(double tiempo) = 0;
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void recibirOro(unsigned int cantidad);
    virtual void dropearItems(Entidad *atacante) = 0;
    virtual void serAtacadoPor(Entidad *atacante) = 0;
    //void atacar(Entidad *objetivo) override;
    void indicarMapaAlQuePertenece(Mapa *mapa);
    void consumirMana(unsigned int cantidad);
    bool manaSuficiente(unsigned int cantidad);
    virtual bool haFinalizado();
    //Serializacion
    const struct PosicionEncapsulada serializarPosicion() const;
    
    friend class Configuraciones;
};

#endif
