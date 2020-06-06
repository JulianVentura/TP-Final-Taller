#ifndef IINTERACTIVO_H
#define IINTERACTIVO_H

#include <SDL2/SDL_events.h>

class IInteractivo {
public:
    virtual void manejarEvento(const SDL_Event& event) = 0;
};

#endif