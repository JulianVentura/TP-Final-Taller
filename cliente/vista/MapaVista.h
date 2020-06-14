#ifndef MAPAVISTA_H
#define MAPAVISTA_H

#include "IRendereable.h"
#include "IInteractivo.h"
#include "Imagen.h"

class MapaVista: public IRendereable, public IInteractivo, 
                                                        public IDimensionable {
public:
    explicit MapaVista(EntornoGrafico& entorno);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void manejarEvento(const SDL_Event& event) override;

private:
    Imagen imagen;
    int x = 0;
    int y = 0;
    int velocidadY = 0;
    int velocidadX = 0;
};
#endif
