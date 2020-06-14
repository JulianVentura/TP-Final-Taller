#ifndef __CRIATURA_H__
#define __CRIATURA_H__
#include "Entidad.h"

class Criatura : public Entidad{
    
    public:
    Criatura(float x, float y, const char* id);
    Criatura(Criatura &&otro) = delete;
    Criatura(Criatura &otro) = delete;
    Criatura& operator=(Criatura &&otro) = delete;
    Criatura& operator=(Criatura &otro) = delete;

    ~Criatura();

};


#endif
