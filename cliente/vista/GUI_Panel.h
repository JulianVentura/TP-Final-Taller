#ifndef __GUI_PANEL_H__
#define __GUI_PANEL_H__

#include <SDL2/SDL_render.h>
#include <atomic>

#include "../vista/BancoImagenesEquipo.h"
#include "../vista/Colores.h"

#define LADO_CASILLA 50
#define SEPARACION 4

class GUI_Panel : public IRendereable{
protected:
	BancoImagenesEquipo& imagenes_equipo;
	Colores& paleta;
	std::atomic<uint16_t>* inventario;
	void dibujarCasilla(int i, int j, SDL_Color& fondo);
public:
	SDL_Rect marco;
	bool visible;
	GUI_Panel(EntornoGrafico& entorno, Colores& paleta, BancoImagenesEquipo&
	 imagenes_equipo, std::atomic<uint16_t>* inventario, SDL_Rect marco);
	void render();
};

#endif /*__GUI_PANEL_H__*/
