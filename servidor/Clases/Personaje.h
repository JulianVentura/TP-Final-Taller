#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"

class Personaje : public Entidad{

    public:
    Personaje(float x, float y, std::string id);
    Personaje(Personaje &otro) = delete;
    Personaje(Personaje &&otro) = delete;
    Personaje& operator=(Personaje &otro) = delete;
    Personaje& operator=(Personaje &&otro);
    ~Personaje();
};

#endif
