#ifndef __ORGANIZADOR_SALAS_H__
#define __ORGANIZADOR_SALAS_H__
#include "Sala.h"
#include <map>
#include <memory>
class OrganizadorSalas{
    private:
    std::map<std::string, std::unique_ptr<Sala>> salas;
    public:
    OrganizadorSalas();
    Sala* obtenerSala(std::string id);
    void comenzar();
    void finalizar();
};

#endif
