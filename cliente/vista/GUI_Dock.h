#ifndef __GUI_DOCK_H__
#define __GUI_DOCK_H__

#include "../vista/IRendereable.h"
#include "../vista/Colores.h"
#include "../vista/Imagen.h"
class GUI_Dock final : public IRendereable{
private:
	Imagen fondo, borde;
	Colores& paleta;
	SDL_Rect marco;
	int x,y;
	int ancho, alto;
	int nimg;
	bool visible;
public:
	GUI_Dock(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_DOCK_H__*/
