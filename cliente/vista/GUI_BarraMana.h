#ifndef __GUI_BARRA_MANA_H__
#define __GUI_BARRA_MANA_H__

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_BarraMana final : public GUI_Barra{
private:
	int capacidad, capacidad_max;
public:
	GUI_BarraMana(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	~GUI_BarraMana();
};

#endif /*__GUI_BARRA_MANA_H__*/