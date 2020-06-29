#ifndef PERSONAJEVISTA_H
#define PERSONAJEVISTA_H

#include "AnimacionEnteDireccionable.h"
#include "IRendereable.h"
#include "IInteractivo.h"
#include "ITargeteable.h"
#include "Imagen.h"
#include "../modelo/ServidorProxy.h"
#include "MovibleVista.h"

class PersonajeVista: public MovibleVista, public IInteractivo {
public:
    PersonajeVista(EntornoGrafico& entorno, Personaje& modelo, std::string& id): 
                                    MovibleVista(entorno, modelo, id) {}
    void manejarEvento(const SDL_Event& event) override;
};

#endif
