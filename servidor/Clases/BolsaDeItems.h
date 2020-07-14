#ifndef __BOLSA_DE_ITEMS_H__
#define __BOLSA_DE_ITEMS_H__

#include "Entidad.h"
#include <vector>
#include <atomic>
class Personaje;
class Item;
class BolsaDeItems : public Entidad{
    private:
    static std::atomic<uint32_t> contadorInstancias;
    std::vector<Item*> items;
    Item* itemNulo;
    uint32_t elementos;
    bool bolsaVacia;
    uint32_t tamBolsa;
    public:
    BolsaDeItems(Posicion posicion, std::vector<Item*> items);
    BolsaDeItems(Posicion posicion, Item *item);
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

    bool haFinalizado() override;
    ~BolsaDeItems() override;
};

#endif