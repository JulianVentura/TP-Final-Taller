#ifndef PERSONAJEVISTA_H
#define PERSONAJEVISTA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "ITargeteable.h"
#include "Imagen.h"

class PersonajeVista: public IRendereable, public IInteractivo, 
                                                        public ITargeteable {
public:
    explicit PersonajeVista(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Imagen imagen;
    std::string ultimo_estado;
};

#endif
