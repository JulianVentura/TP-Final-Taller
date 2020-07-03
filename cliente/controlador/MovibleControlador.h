#ifndef MOVIBLECONTROLADOR_H
#define MOVIBLECONTROLADOR_H

#include <unordered_map>
#include "IInteractivo.h"
#include "../modelo/Movible.h"

class MovibleControlador: public IInteractivo {
public:
    explicit MovibleControlador(Movible& modelo);
    void manejarEvento(const SDL_Event& event) override;

private:
    Movible& modelo;
    int ultima_tecla_presionada;
    static std::unordered_map<int, uint32_t> teclas_direccionables;
};

#endif
