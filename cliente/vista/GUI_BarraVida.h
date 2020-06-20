#ifndef __GUI_BARRA_VIDA_H__
#define __GUI_BARRA_VIDA_H__

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_BarraVida final : public GUI_Barra{
private:
	int capacidad, capacidad_max;
public:
	GUI_BarraVida(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	~GUI_BarraVida();
};

#endif /*__GUI_BARRA_VIDA_H__*/