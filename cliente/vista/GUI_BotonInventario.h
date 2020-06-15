#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include "IRendereable.h"
#include "Imagen.h"

#define LADO_BOTON 50
#define SEPARACION 4

class GUI_BotonInventario final : public IRendereable{
public:
	Imagen imagen;
	int x,y;
	int x_cuadro,y_cuadro;
	int ancho, alto;
	SDL_Color frente, fondo, sombra, luz;
	bool visible;
	GUI_BotonInventario(EntornoGrafico& entorno, int x, int y);
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/