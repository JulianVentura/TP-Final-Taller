#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include <atomic>

#include "../modelo/DatosPersonaje.h"
#include "../vista/BancoImagenesEquipo.h"
#include "../vista/IRendereable.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

class GUI_BotonInventario final : public IRendereable{
public:
	int x,y;
	Imagen imagen;
	GUI_BotonInventario(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/