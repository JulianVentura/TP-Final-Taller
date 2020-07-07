#ifndef __SACERDOTE_H__
#define __SACERDOTE_H__
#include "Interactuable.h"

class Personaje;
class Sacerdote : public Interactuable{
    public:
    Sacerdote(float x, float y);
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    void curar(Personaje *personaje, Cliente *cliente);
    ~Sacerdote() override;
};

#endif