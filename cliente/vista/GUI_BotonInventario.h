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
	void dibujarCasilla(int i, int j, SDL_Color& fondo);
public:
	int x,y;
	int ancho, alto;
	bool visible;
	GUI_BotonInventario(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/