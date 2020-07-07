#ifndef __ESTADO_H__
#define __ESTADO_H__

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

    public:
    Estado(Personaje *unPersonaje);
    virtual void interactuarCon(Entidad *entidad);
    virtual void interactuar(Entidad *entidad) = 0;
    virtual void atacar(Entidad *objetivo, Arma *arma) = 0;
    virtual void actualizar(double tiempo, Mapa *mapa) = 0;
    virtual void recibirDanio(int danio, Entidad *atacante) = 0;
    virtual void meditar() = 0;
    virtual void dejarDeMeditar() = 0;
    virtual void pedirCuracion(Sacerdote *sacerdote, Cliente *cliente) = 0;
    virtual void pedirListado(Interactuable *interactuable, Cliente *cliente) = 0;
    virtual void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) = 0;
    virtual void pedirVenta(Item *item, Interactuable *interactuable, Cliente *cliente) = 0;

    virtual ~Estado();
};


#endif

