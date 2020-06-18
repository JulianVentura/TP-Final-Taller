#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include "IRendereable.h"
#include "Imagen.h"
#include "Colores.h"

#define LADO_BOTON 50
#define SEPARACION 4

class GUI_BotonInventario final : public IRendereable{
private:
	Imagen imagen;
	Colores& paleta;
	int x,y;
	int x_cuadro,y_cuadro;
	int ancho, alto;
	void dibujarCasilla(int i, int j, SDL_Color& fondo);
public:
	bool visible;
	GUI_BotonInventario(EntornoGrafico& entorno, Colores& paleta, int x, int y);
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/