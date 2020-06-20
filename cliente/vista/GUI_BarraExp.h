#ifndef __GUI_BARRA_EXP_H__
#define __GUI_BARRA_EXP_H__

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_BarraExp final : public GUI_Barra{
private:
	int capacidad, capacidad_max;
public:
	GUI_BarraExp(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	~GUI_BarraExp();
};

#endif /*__GUI_BARRA_EXP_H__*/