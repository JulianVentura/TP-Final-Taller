#ifndef __FABRICA_DE_NPC_H__
#define __FABRICA_DE_NPC_H__
#include "Entidad.h"
#include "Criatura.h"
#include <map>
#include <memory>

class FabricaDeNPC{
    private:
    const std::unordered_map<std::string, Entidad*> &entidades;
    unsigned long contador;

    bool idValido(std::string id) const;

    public:
    FabricaDeNPC(const std::unordered_map<std::string, Entidad*> &entidades);
    std::unique_ptr<Criatura> obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa);

    std::unique_ptr<Entidad> obtenerNPCPasivo(const float x, 
                                              const float y, 
                                              const std::string &idNPC, 
                                              const std::string &idMapa);
};


#endif
