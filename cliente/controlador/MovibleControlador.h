#ifndef MOVIBLECONTROLADOR_H
#define MOVIBLECONTROLADOR_H

#include <unordered_map>
#include "IInteractivo.h"
#include "../modelo/ServidorProxy.h"

class MovibleControlador: public IInteractivo {
public:
    explicit MovibleControlador(ServidorProxy& servidor);
    bool manejarEvento(SDL_Event& evento) override;

private:
    ServidorProxy& servidor;
    int ultima_tecla_presionada = 0;
    static std::unordered_map<int, uint32_t> teclas_direccionables;
};

#endif
