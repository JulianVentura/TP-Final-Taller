#ifndef __GUI_BOTON_H__
#define __GUI_BOTON_H__

#include <SDL2/SDL_rect.h>
#include <string>

#include "../vista/Colores.h"
#include "../vista/Ventana.h"
#include "../vista/IRendereable.h"
#include "../vista/Imagen.h"

class GUI_Boton :  public IRendereable{
protected:
	int x,y;
	Imagen imagen;
public:
	GUI_Boton(EntornoGrafico& entorno, std::string ruta);
	virtual void actualizarDimension();
	virtual void render();
	virtual SDL_Rect obtenerMarco();
};

#endif /*__GUI_BOTON_H__*/