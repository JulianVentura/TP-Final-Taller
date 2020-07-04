#ifndef __CRIATURA_H__
#define __CRIATURA_H__
#include "Entidad.h"
#include "FabricaDeItems.h"

class Criatura : public Entidad{
    
    public:
    Criatura(float x, float y, std::string id, FabricaDeItems &fabricaItems);
    Criatura(Criatura &&otro) = delete;
    Criatura(Criatura &otro) = delete;
    Criatura& operator=(Criatura &&otro) = delete;
    Criatura& operator=(Criatura &otro) = delete;
    void agregarDiferenciador(const unsigned int numero);
    ~Criatura();

};


#endif
