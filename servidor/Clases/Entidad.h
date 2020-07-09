#ifndef __ENTIDAD_H__
#define __ENTIDAD_H__
#include "Posicionable.h"
#include "Colisionable.h"
#include "Configuraciones.h"
#include "Arma.h"
#include "Inventario.h"
#include <string>

class Mapa;
class Personaje;
class Criatura;
class Divulgador;
class Entidad : public Colisionable, public Posicionable {
    protected:
    uint32_t vidaMaxima;
    uint32_t vidaActual;
    uint32_t manaMaximo;
    uint32_t manaActual;
    uint32_t fuerza;
    uint32_t inteligencia;
    uint32_t agilidad;
    uint32_t constitucion;
    uint32_t nivel;
    std::string id;
    Arma *arma;
    Inventario inventario;
    Mapa *mapaAlQuePertenece;

    public:
    virtual ~Entidad();
    //Por ser colisionable
    Entidad(std::string id);
    virtual const quadtree::Box<float>& obtenerArea() const override;
    virtual bool colisionaCon(const Colisionable &otro) const override;
    virtual bool colisionaCon(const quadtree::Box<float> &area) const override;
    //Por ser posicionable
    virtual const std::string obtenerId() const;
    virtual void actualizarEstado(double tiempo, Mapa *mapa);

    virtual void atacar(Personaje *objetivo, Divulgador *divulgador) = 0;
    virtual void atacar(Criatura *objetivo, Divulgador *divulgador) = 0;
    virtual void serAtacadoPor(Personaje *atacante, Divulgador *divulgador) = 0;
    virtual void serAtacadoPor(Criatura *atacante, Divulgador *divulgador) = 0;
    virtual void recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador);
    virtual void obtenerExperiencia(unsigned int cantidad);
    virtual void recibirOro(unsigned int cantidad);
    virtual void dropearItems(Entidad *atacante) = 0;
    void indicarMapaAlQuePertenece(Mapa *mapa);
    void consumirMana(unsigned int cantidad);
    bool manaSuficiente(unsigned int cantidad);
    void equipar(Arma *arma);
    void almacenar(Item *item);
    friend class Configuraciones;
};

#endif
