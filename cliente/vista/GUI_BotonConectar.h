#ifndef __GUI_BOTON_CONECTAR_H__
#define __GUI_BOTON_CONECTAR_H__

#include <atomic>

#include "../vista/Ventana.h"
#include "../vista/IRendereable.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"
#include "../vista/Imagen.h"

class GUI_BotonConectar final : public IRendereable{
public:
	int x,y;
	Imagen imagen;
	GUI_BotonConectar(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_BOTON_NUEVA_CUENTA_H__*/
