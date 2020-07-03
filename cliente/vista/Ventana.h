#ifndef VENTANA_H
#define VENTANA_H

#include "EntornoGrafico.h"
#include "../controlador/IInteractivo.h"
#include "IRendereable.h"
#include "IDimensionable.h"
#include "Renderer.h"
#include <SDL2/SDL_events.h>
#include <vector>

class Ventana: public IDimensionable, public IInteractivo, public IRendereable {
public:
    Ventana(EntornoGrafico& entorno, const char* title);
    ~Ventana();

    void manejarEvento(const SDL_Event& event) override;
    /**
     * @brief Llamará al método render de los rendereables que fueron agregados
     * en el orden que fueron agregados. Luego se presentará en pantalla.
     */
    void render() override;
    void actualizar(unsigned int delta_t) override;
    
private:
    bool pantalla_completa = false;
    SDL_Window* ventana;
    Renderer* renderer;
    SDL_Color color_fondo = {51, 51, 51, 255};
    EntornoGrafico& entorno;
    friend class Renderer;
};
#endif
