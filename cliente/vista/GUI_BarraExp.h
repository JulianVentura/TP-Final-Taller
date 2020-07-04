#ifndef __GUI_BARRA_EXP_H__
#define __GUI_BARRA_EXP_H__

#include <atomic>

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_BarraExp final : public GUI_Barra{
public:
	GUI_BarraExp(EntornoGrafico& entorno, Colores& paleta,
	  std::atomic<int>& exp_max , std::atomic<int>& exp);
	void actualizarDimension();
	~GUI_BarraExp();
};

#endif /*__GUI_BARRA_EXP_H__*/
