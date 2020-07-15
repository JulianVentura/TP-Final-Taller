#ifndef __SACERDOTE_H__
#define __SACERDOTE_H__
#include "Comerciante.h"

class Personaje;
class Sacerdote : public Comerciante{
    public:
    Sacerdote(float x, float y);
    void serAtacadoPor(Personaje *atacante) override;
    bool curar(Personaje *personaje, Cliente *cliente);
    ~Sacerdote() override; 
};

#endif