#ifndef __CRIATURA_H__
#define __CRIATURA_H__
#include "Entidad.h"

class Criatura : public Entidad{
    private:
    unsigned int diferenciador;
    public:
    Criatura(float x, float y, std::string id);
    Criatura(Criatura &&otro) = delete;
    Criatura(Criatura &otro) = delete;
    Criatura& operator=(Criatura &&otro) = delete;
    Criatura& operator=(Criatura &otro) = delete;
    void agregarDiferenciador(const unsigned int numero);
    void dropearItems(Entidad *atacante) override;
    const std::string obtenerId() const override;
    ~Criatura();

};


#endif
