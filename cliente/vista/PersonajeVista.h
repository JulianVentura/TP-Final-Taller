#ifndef PERSONAJEVISTA_H
#define PERSONAJEVISTA_H

#include "AnimacionEnteDireccionable.h"
#include "IRendereable.h"
#include "IInteractivo.h"
#include "ITargeteable.h"
#include "Imagen.h"
#include "Personaje.h"


class PersonajeVista: public IRendereable, public IInteractivo, 
                                                        public ITargeteable {
public:
    PersonajeVista(EntornoGrafico& entorno, Personaje& modelo);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;


private:
    Personaje& personajeModelo;
    Imagen imagen;
    AnimacionEnteDireccionable animacion;
    std::string ultimo_estado;
};

#endif
