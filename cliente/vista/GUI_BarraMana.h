#ifndef __GUI_BARRA_MANA_H__
#define __GUI_BARRA_MANA_H__

#include <atomic>

#include "../vista/GUI_Barra.h"
#include "../vista/Colores.h"
#include "EntornoGrafico.h"
#include "IRendereable.h"

class GUI_BarraMana final : public GUI_Barra{
public:
	GUI_BarraMana(EntornoGrafico& entorno, Colores& paleta,
	 std::atomic<uint16_t>& mana_max , std::atomic<uint16_t>& mana);
	void actualizarDimension();
	~GUI_BarraMana();
};

#endif /*__GUI_BARRA_MANA_H__*/
