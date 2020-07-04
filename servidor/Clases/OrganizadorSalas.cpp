#include "OrganizadorSalas.h"
#include "Excepcion.h"


OrganizadorSalas::OrganizadorSalas(const char *archivoConfig){
    Configuraciones::crearInstancia(archivoConfig);
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::vector<std::string> listaSalas = config->obtenerSalas();
    for (auto &sala : listaSalas){
        salas[sala] = std::move(std::unique_ptr<Sala>(new Sala(sala)));
    }
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