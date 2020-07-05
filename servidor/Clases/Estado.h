#ifndef __ESTADO_H__
#define __ESTADO_H__

class Arma;
class Entidad;
class Personaje;
class Mapa;
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

    virtual ~Estado();
};


#endif

