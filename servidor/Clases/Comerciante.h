#ifndef __COMERCIANTE_H__
#define __COMERCIANTE_H__

#include "Entidad.h"
#include <vector>

class Personaje;
class Item;
class Comerciante : public Entidad{
    protected:
    std::vector<Item*> items;
    Item* itemNulo;
    uint32_t tamTienda;
    
    public:
    Comerciante(float x, float y);
    //Ataques
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
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
    std::vector<SerializacionItem> serializarTienda();
    ~Comerciante() override;
};

#endif