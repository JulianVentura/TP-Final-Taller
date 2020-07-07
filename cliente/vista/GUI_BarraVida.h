#ifndef __GUI_BARRA_VIDA_H__
#define __GUI_BARRA_VIDA_H__

#include <atomic>

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"



class GUI_BarraVida final : public GUI_Barra{
public:
	GUI_BarraVida(EntornoGrafico& entorno, Colores& paleta,
	  std::atomic<uint16_t>& vida_max , std::atomic<uint16_t>& vida);
	void actualizarDimension();
	~GUI_BarraVida();
};

#endif /*__GUI_BARRA_VIDA_H__*/
