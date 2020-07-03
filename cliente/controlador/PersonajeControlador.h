#ifndef PERSONAJECONTROLADOR_H
#define PERSONAJECONTROLADOR_H

#include <unordered_map>
#include "IInteractivo.h"
#include "../modelo/Personaje.h"

class PersonajeControlador: public IInteractivo {
public:
    explicit PersonajeControlador(Personaje& modelo);
    void manejarEvento(const SDL_Event& event) override;

private:
    Personaje& modelo;
    int ultima_tecla_presionada;
    static std::unordered_map<int, uint32_t> teclas_direccionables;
};

#endif
