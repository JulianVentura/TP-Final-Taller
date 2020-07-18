#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Movible.h"
#include "Interactuable.h"
#include "Configuraciones.h"
#include "Inventario.h"
#include "../../common/Serializacion.h"
#include <string>

class Mapa;
class Entidad : public Interactuable{
    protected:
    uint32_t vidaMaxima;
    float vidaActual;
    uint32_t manaMaximo;
    float manaActual;
    uint32_t fuerza;
    uint32_t inteligencia;
    uint32_t agilidad;
    uint32_t constitucion;
    uint32_t nivel;
    Arma *arma;
    Mapa *mapaAlQuePertenece;

    public:
    virtual ~Entidad();
    Entidad(std::string id);
    virtual void actualizarEstado(double tiempo) = 0;
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void recibirOro(unsigned int cantidad);
    virtual std::string dropearItems(Entidad *atacante) = 0;
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
