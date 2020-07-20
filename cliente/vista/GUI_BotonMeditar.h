#ifndef __GUI_BOTON_MEDITAR_H__
#define __GUI_BOTON_MEDITAR_H__

#include "../vista/GUI_Boton.h"

class GUI_BotonMeditar final : public GUI_Boton{
public:
	GUI_BotonMeditar(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_BOTON_MEDITAR_H__*/