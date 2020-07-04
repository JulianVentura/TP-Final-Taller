#ifndef __FABRICA_DE_CRIATURAS_H__
#define __FABRICA_DE_CRIATURAS_H__
#include "Criatura.h"
#include "FabricaDeItems.h"
#include <map>
#include <memory>
class FabricaDeCriaturas{
    private:
    const std::map<std::string, std::unique_ptr<Criatura>> &criaturas;
    FabricaDeItems fabricaItems;
    unsigned long contador;

    bool idValido(std::string id) const;
    public:
    FabricaDeCriaturas(const std::map<std::string, std::unique_ptr<Criatura>> &criaturas);
    std::unique_ptr<Criatura> obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa);
};


#endif
