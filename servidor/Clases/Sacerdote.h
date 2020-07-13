#ifndef __SACERDOTE_H__
#define __SACERDOTE_H__
#include "Entidad.h"

class Personaje;
class Sacerdote : public Entidad{
    public:
    Sacerdote(float x, float y);
    //Ataques
    void atacar(Personaje *objetivo) override;
    void atacar(Criatura *objetivo) override;
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
    bool curar(Personaje *personaje, Cliente *cliente);
    //Estado
    void actualizarEstado(double tiempo) override;
    void dropearItems(Entidad *atacante) override;
    ~Sacerdote() override; 
};

#endif