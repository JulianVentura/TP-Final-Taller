#ifndef __ORGANIZADOR_SALAS_H__
#define __ORGANIZADOR_SALAS_H__
#include "Sala.h"
#include <map>
#include <memory>
#include "ColaDeSerializacion.h"
class OrganizadorSalas{
    private:
    std::map<std::string, std::unique_ptr<Sala>> salas;
    public:
    OrganizadorSalas(const char *archivoConfig, ColaSerializacion &cola);
    Sala* obtenerSala(std::string id);
    void comenzar();
    void finalizar();
};

#endif
