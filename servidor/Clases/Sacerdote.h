#ifndef __SACERDOTE_H__
#define __SACERDOTE_H__
#include "Comerciante.h"

class Personaje;
class Sacerdote : public Comerciante{
    public:
    Sacerdote(float x, float y);
    /*
    Sana al atacante, reviviendolo en caso de que sea fantasma.
    En caso de que la distancia entre el Sacerdote y el atacante sea mayor a la distancia de interaccion 
    la interaccion no se realizara y se le enviara al cliente un mensaje descriptivo.
    */
    void serAtacadoPor(Personaje *atacante) override;
    ~Sacerdote() override; 
};

#endif