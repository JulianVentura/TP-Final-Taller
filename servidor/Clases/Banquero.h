#ifndef __BANQUERO_H__
#define __BANQUERO_H__

#include "Item.h"
#include "Entidad.h"

#include <vector>

class Personaje;
class Item;
class Banquero : public Entidad{
    private:
    uint32_t tamAlmacen;
    Item* itemNulo;
    public:
    Banquero(float x, float y);
    //Ataques
    void atacar(Personaje *objetivo) override;
    void atacar(Criatura *objetivo) override;
    void serAtacadoPor(Entidad *atacante) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    bool recibirDanio(int danio, Entidad *atacante) override;
    //Comercio
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    //Estado
    void actualizarEstado(double tiempo) override;
    void dropearItems(Entidad *atacante) override;
    ~Banquero() override;
};

#endif
