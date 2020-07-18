#ifndef __BANQUERO_H__
#define __BANQUERO_H__

#include "Item.h"
#include "Entidad.h"
#include <vector>

class Personaje;
class Item;
class Banquero : public Entidad{
    private:
    uint32_t limiteTransaccion;
    float fraccionTransaccion;
    Item* itemNulo;
    public:
    Banquero(float x, float y);
    //Ataques
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
    void recibirCuracion(unsigned int curacion, Entidad *lanzador) override;
    //Comercio
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;
    void transaccion(bool esDeposito, Personaje *personaje, Cliente *cliente);
    //Estado
    void actualizarEstado(double tiempo) override;
    void dropearItems(Entidad *atacante) override;
    SerializacionContenedor serializarAlmacen(const std::vector<Item*> &almacen, uint32_t oro);
    ~Banquero() override;
};

#endif
