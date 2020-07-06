#ifndef IINTERACTIVO_H
#define IINTERACTIVO_H

#include <SDL2/SDL_events.h>

class IInteractivo {
public:
    virtual bool manejarEvento(SDL_Event& evento) = 0;
};
#endif
