#ifndef __INTERACTUABLE_H__
#define __INTERACTUABLE_H__
#include "Movible.h"
#include <string>
#define ATAQUE_NO_REALIADO -1
#define GOLPE_ESQUIVADO -2

class Estado;
class Cliente;
class Item;
class Personaje;
class Criatura;
class Personaje;
class Entidad;
class Interactuable : public Movible{
    protected:
    std::string id;
    float distanciaMaximaDeInteraccion;

    public:
    Interactuable(std::string id);
    //Comercio
    virtual void interactuar(Estado *estado, Cliente *cliente) = 0;
    virtual void comprar(unsigned int pos, Estado *estado, Cliente *cliente) = 0;
    virtual void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) = 0;
    virtual void vender(unsigned int pos, Estado *estado, Cliente *cliente) = 0;
    virtual void vender(Item* item, Personaje *personaje, Cliente *cliente) = 0;
    virtual void listar(Personaje *personaje, Cliente *cliente) = 0;
    virtual void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) = 0;
    //Ataques
    virtual std::string atacar(Personaje *objetivo) = 0;
    virtual std::string atacar(Criatura *objetivo) = 0;
    virtual void serAtacadoPor(Personaje *atacantem) = 0;
    virtual void serAtacadoPor(Criatura *atacante) = 0;
    virtual std::string recibirDanio(int danio, Entidad *atacante) = 0;
    virtual void recibirCuracion(unsigned int curacion, Entidad *lanzador) = 0;

    virtual const std::string obtenerId() const;
    virtual ~Interactuable();
};  

#endif
