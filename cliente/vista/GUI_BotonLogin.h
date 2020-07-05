#ifndef __GUI_BOTON_LOGIN_H__
#define __GUI_BOTON_LOGIN_H__

#include "../vista/Ventana.h"
#include "../vista/IRendereable.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

class GUI_BotonLogin final : public IRendereable{
public:
	int x,y;
	Imagen imagen;
	GUI_BotonLogin(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_BOTON_NUEVA_CUENTA_H__*/
