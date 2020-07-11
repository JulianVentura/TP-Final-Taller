#ifndef __FABRICA_DE_CRIATURAS_H__
#define __FABRICA_DE_CRIATURAS_H__
#include "Entidad.h"
#include "Criatura.h"
#include <map>
#include <memory>

class FabricaDeCriaturas{
    private:
    const std::unordered_map<std::string, Entidad*> &entidades;
    unsigned long contador;

    bool idValido(std::string id) const;

    public:
    FabricaDeCriaturas(const std::unordered_map<std::string, Entidad*> &entidades);
    std::unique_ptr<Criatura> obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa);
};


#endif
