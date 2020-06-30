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
    PersonajeVista(EntornoGrafico& entorno, Personaje& modelo, std::string& id,
         ServidorProxy& servidor): 
            MovibleVista(entorno, modelo, id), 
            servidor(servidor) {}
    void manejarEvento(const SDL_Event& event) override;
    void actualizar(unsigned int delta_t) override;
    
private:
    ServidorProxy& servidor;
};

#endif
