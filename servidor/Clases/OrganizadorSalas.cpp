#include "OrganizadorSalas.h"
#include "Excepcion.h"


OrganizadorSalas::OrganizadorSalas(){
    salas["mapa1"] = std::unique_ptr<Sala>(new Sala("mapa1"));
}
Sala* OrganizadorSalas::obtenerSala(std::string id){
    std::map<std::string, std::unique_ptr<Sala>>::iterator it = salas.find(id);
    if (it == salas.end()){
        throw Excepcion("Error en OrganizadorSalas: La sala de id %s es inexistente", id.c_str());
    }
    return it->second.get();
}