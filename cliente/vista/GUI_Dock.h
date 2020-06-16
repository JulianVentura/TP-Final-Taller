#ifndef __GUI_DOCK_H__
#define __GUI_DOCK_H__

#include "IRendereable.h"
#include "Colores.h"

class GUI_Dock final : public IRendereable{
private:
	Colores& paleta;
	SDL_Rect marco;
	int x,y;
	int ancho, alto;
	bool visible;
public:
	GUI_Dock(EntornoGrafico& entorno, Colores& paleta);
	void actualizar_dimensiones();
	void render();
};

#endif /*__GUI_DOCK_H__*/