#ifndef __ESTADO_H__
#define __ESTADO_H__
#include <cstdint>
class Divulgador;
class Arma;
class Entidad;
class Personaje;
class Mapa;
class Interactuable;
class Cliente;
class Item;
class Sacerdote;
class Estado{
    protected:
    Personaje *personaje;
    uint16_t idTCP;

    public:
    Estado(Personaje *unPersonaje);
    virtual void interactuarCon(Entidad *entidad);
    virtual void interactuar(Entidad *entidad) = 0;
    virtual void atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador) = 0;
    virtual void actualizar(double tiempo, Mapa *mapa) = 0;
    virtual void recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador) = 0;
    virtual void serAtacadoPor(Entidad *atacante, Divulgador *divulgador) = 0;
    virtual void meditar() = 0;
    virtual void dejarDeMeditar() = 0;
    virtual void pedirCuracion(Sacerdote *sacerdote, Cliente *cliente) = 0;
    virtual void pedirListado(Interactuable *interactuable, Cliente *cliente) = 0;
    virtual void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) = 0;
    virtual void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) = 0;
    const uint16_t obtenerIDTCP() const;

    virtual ~Estado();
};


#endif

