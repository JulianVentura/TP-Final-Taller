#include "OrganizadorSalas.h"
#include "Excepcion.h"


OrganizadorSalas::OrganizadorSalas(){
    salas["mapa1"] = std::move(std::unique_ptr<Sala>(new Sala("mapa1")));
}
Sala* OrganizadorSalas::obtenerSala(std::string id){
    std::map<std::string, std::unique_ptr<Sala>>::iterator it = salas.find(id);
    if (it == salas.end()){
        throw Excepcion("Error en OrganizadorSalas: La sala de id %s es inexistente", id.c_str());
    }
    return it->second.get();
}

void OrganizadorSalas::comenzar(){
    for (auto &sala : salas){
        sala.second->comenzar();
    }
}

void OrganizadorSalas::finalizar(){
    for (auto &sala : salas){
        sala.second->finalizar();
    }
}